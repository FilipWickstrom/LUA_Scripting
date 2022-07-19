#include "PCH.h"
#include "SceneHandler.h"
#include "CppToLua.h"

SceneHandler::SceneHandler()
{
    m_spriteUID = 0;
    m_guiUID = 0;
    m_camera = nullptr;
}

SceneHandler::~SceneHandler()
{
}

auto& SceneHandler::Get()
{
    static SceneHandler instance;
    return instance;
}

void SceneHandler::LoadStartScene()
{
    bool loadedScene = false;

    //Reading what scene to start with
    LoadScript("AllScenes.lua");

    //Get the current state
    lua_getglobal(LUA, "startScene");
    if (lua_isstring(LUA, -1))
    {
        std::string filename = lua_tostring(LUA, -1);
        lua_pop(LUA, 1);

        loadedScene = Get().LoadScene(filename);
    }

    if (!loadedScene)
    {
        std::cout << "Scene error: 'startScene' was not correct in 'AllScenes.lua'..." << std::endl;
        Graphics::GetDevice()->closeDevice();
    }
}

void SceneHandler::ChangeScene(const std::string& file)
{
    // Empty file means that we are closing down the program
    // and cleaning up the current scene.
    if (file.empty())
    {
        Get().ResetScene();
        Graphics::GetDevice()->closeDevice();
        return;
    }

    // Still same scene
    if (file == Get().m_currentScene) return;

    Get().m_currentScene = file;


    //Clean up previous scene
    Get().ResetScene();

    LuaHandler::ResetState();

    //Load in the new scene
    Get().LoadScene(file);
}

void SceneHandler::UpdateScene()
{
    //Update the scene according to lua
    lua_getglobal(LUA, "Update");
    lua_pushnumber(LUA, Graphics::GetDeltaTime());
    LuaHandler::CheckErrors(1, 0);
}

void SceneHandler::ResetScene()
{
    /*
        Cleaning up in C++
    */
    Graphics::GetSceneManager()->clear();
    Graphics::GetSceneManager()->getMeshCache()->clear();
    Graphics::GetGUIEnvironment()->clear();
    Graphics2D::RemoveAll();

    m_spriteUID = 0;
    m_guiUID = 0;

    m_sprites.clear();
    m_texts.clear();

    //Removing active camera
    irr::scene::ICameraSceneNode* oldCam = Graphics::GetSceneManager()->getActiveCamera();
    if (oldCam)
        oldCam->remove();
    
    Graphics::GetSceneManager()->setActiveCamera(0);
    m_camera = nullptr;
}

bool SceneHandler::LoadScene(const std::string& file)
{
    if (LoadScript(file))
    {
        lua_getglobal(LUA, "Start");
        LuaHandler::CheckErrors(0, 0);

#if DEBUG_LUA_GLOBALS
        lua_getglobal(LUA, "PrintAllGlobals");
        LuaHandler::CheckErrors(0, 0);
#endif

        return true;
    }
    return false;
}

unsigned int SceneHandler::AddSprite(const std::string& file)
{
    unsigned int id = Get().m_spriteUID++;
    Get().m_sprites.emplace(id, std::make_unique<Sprite>(file, id));
    return id;
}

void SceneHandler::RemoveSprite(const unsigned int& id)
{
    if (Get().m_sprites.find(id) != Get().m_sprites.end())
    {
        Get().m_sprites.at(id)->Remove();
        Get().m_sprites.erase(id);
    }
}

void SceneHandler::ChangeSprite(const unsigned int& id, const std::string& file)
{
    if (Get().m_sprites.find(id) != Get().m_sprites.end())
        Get().m_sprites.at(id)->LoadTexture(file);
}

void SceneHandler::SetSpriteVisible(const unsigned int& id, const bool& isVisible)
{
    if (Get().m_sprites.find(id) != Get().m_sprites.end())
    {
        Get().m_sprites.at(id)->SetVisible(isVisible);
    }
}

void SceneHandler::SetSpritePosition(const unsigned int& id, const irr::core::vector3df& pos)
{
    if (Get().m_sprites.find(id) != Get().m_sprites.end())
        Get().m_sprites.at(id)->SetPosition(pos);
}

void SceneHandler::SetSpriteScale(const unsigned int& id, const irr::core::vector3df& scl)
{
    if (Get().m_sprites.find(id) != Get().m_sprites.end())
        Get().m_sprites.at(id)->SetScale(scl);
}

void SceneHandler::SetSpriteRotation(const unsigned int& id, const irr::core::vector3df& rot)
{
    if (Get().m_sprites.find(id) != Get().m_sprites.end())
        Get().m_sprites.at(id)->SetRotation(rot);
}

void SceneHandler::SetHasCollision(const unsigned int& id, const bool& enabled)
{
    if (Get().m_sprites.find(id) != Get().m_sprites.end())
        Get().m_sprites.at(id)->SetCollision(enabled);
}

bool SceneHandler::SpriteCollisionAABB(const unsigned int& id1, const unsigned int& id2)
{
    if (Get().m_sprites.find(id1) != Get().m_sprites.end() &&
        Get().m_sprites.find(id2) != Get().m_sprites.end())
    {
        // Return false if one of them don't use collision
        if (!Get().m_sprites.at(id1)->HasCollision() ||
            !Get().m_sprites.at(id2)->HasCollision())
        {
            return false;
        }

        // Optimizing by checking if in range
        if (SpriteCollisionCircle(id1, id2))
        {
		    const auto& rect1 = Get().m_sprites.at(id1)->GetBounds();
		    const auto& rect2 = Get().m_sprites.at(id2)->GetBounds();

	        // Checking if one rectangle is inside on the other
            return rect1.isRectCollided(rect2);
        }
    }

    return false;
}

bool SceneHandler::SpriteCollisionCircle(const unsigned int& id1, const unsigned int& id2)
{
    if (Get().m_sprites.find(id1) != Get().m_sprites.end() &&
        Get().m_sprites.find(id2) != Get().m_sprites.end())
    {
        const Sprite* sprite1 = Get().m_sprites.at(id1).get();
        const Sprite* sprite2 = Get().m_sprites.at(id2).get();

        // Return false if one of them don't use collision
        if (!sprite1->HasCollision() ||
            !sprite2->HasCollision())
        {
            return false;
        }

        irr::core::vector2df pos1 = sprite1->GetPosition2D();
        float dist1 = sprite1->GetCollisionRadius();
        irr::core::vector2df pos2 = sprite2->GetPosition2D();
        float dist2 = sprite2->GetCollisionRadius();

        // [OPTIMIZE] Can use getDistanceFromSQ() to avoid square root for better performance

        // Distance between the two points
        float posDist = pos1.getDistanceFrom(pos2);

        // Checking if any of the distances is smaller than any of the radiuses
        return (posDist < dist1 + dist2);
    }

    return false;
}

void SceneHandler::AddCamera()
{
    float width = static_cast<float>(Graphics::GetWindowWidth());
    float height = static_cast<float>(Graphics::GetWindowHeight());

    //Add a default camera
    Get().m_camera = Graphics::GetSceneManager()->addCameraSceneNode();

    irr::core::matrix4 matrix;
    matrix.buildProjectionMatrixOrthoLH(width, height, 1.f, 100.f);

    Get().m_camera->setProjectionMatrix(matrix, true);

    Graphics::GetSceneManager()->setActiveCamera(Get().m_camera);
}

void SceneHandler::SetCameraPosition(const irr::core::vector3df& pos)
{
    if (Get().m_camera)
        Get().m_camera->setPosition(pos);
}

void SceneHandler::SetCameraTarget(const irr::core::vector3df& tar)
{
    if (Get().m_camera)
        Get().m_camera->setTarget(tar);
}

void SceneHandler::SetCameraZoom(const float& zoom)
{
    if (!Get().m_camera) return;

    float width = static_cast<float>(Graphics::GetWindowWidth());
    float height = static_cast<float>(Graphics::GetWindowHeight());

    float thezoom = zoom;
    //Zoom should not go below 1 and not higher than the resolution
    if (zoom < 1.f)
        thezoom = 1.f;
    else if (zoom > height)
        thezoom = height;
    else if (zoom > width)
        thezoom = width;

    irr::core::matrix4 matrix;
    matrix.buildProjectionMatrixOrthoLH(width / thezoom, height / thezoom, 1.f, 100.f);

    Get().m_camera->setProjectionMatrix(matrix, true);
}

unsigned int SceneHandler::AddText(const std::string& text, const std::string& font, irr::core::vector2di pos, irr::core::vector2di size)
{
    std::wstring wstring(text.begin(), text.end());
    irr::gui::IGUIStaticText* irrText = Graphics::GetGUIEnvironment()->addStaticText
    (
        wstring.c_str(),
        irr::core::rect<irr::s32>(
            pos.X - (size.X / 2),
            pos.Y - (size.Y / 2),
            pos.X + (size.X / 2),
            pos.Y + (size.Y / 2)),
        false, false
    );
#if DEBUG_UI
    irrText->setDrawBackground(true);
#endif

    //Center text by default
    irrText->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);

    //Set an ID for the GUI
    unsigned int id = Get().m_guiUID++;
    irrText->setID(id);

    std::string fontstr = FONTPATH + font;
    irr::gui::IGUIFont* irrfont = Graphics::GetGUIEnvironment()->getFont(fontstr.c_str());
    if (irrfont)
        irrText->setOverrideFont(irrfont);

    Get().m_texts[id] = irrText;

    return id;
}

void SceneHandler::SetTextAlignment(const unsigned int& id, const irr::gui::EGUI_ALIGNMENT& alignment)
{
    if (Get().m_texts.find(id) != Get().m_texts.end())
        Get().m_texts.at(id)->setTextAlignment(alignment, irr::gui::EGUIA_CENTER);
}

void SceneHandler::UpdateText(unsigned int& id, const std::string& text)
{
    if (Get().m_texts.find(id) != Get().m_texts.end())
    {
        std::wstring widestr = std::wstring(text.begin(), text.end());
        Get().m_texts.at(id)->setText(widestr.c_str());
    }
}

unsigned int SceneHandler::AddButton(const std::string& text, const std::string& font, irr::core::vector2di pos, irr::core::vector2di size)
{
    std::wstring wstring(text.begin(), text.end());
    irr::gui::IGUIButton* irrButton = Graphics::GetGUIEnvironment()->addButton
    (
        irr::core::rect<irr::s32>(
            pos.X - (size.X / 2),
            pos.Y - (size.Y / 2),
            pos.X + (size.X / 2),
            pos.Y + (size.Y / 2)),
        0, -1, wstring.c_str()
    );

    //Set an ID for the GUI
    unsigned int id = Get().m_guiUID++;
    irrButton->setID(id);

    std::string fontstr = FONTPATH + font;
    irr::gui::IGUIFont* irrfont = Graphics::GetGUIEnvironment()->getFont(fontstr.c_str());
    if (irrfont)
        irrButton->setOverrideFont(irrfont);

    return id;
}

void SceneHandler::RemoveGUI(unsigned int id)
{
    irr::gui::IGUIElement* elem = Graphics::GetGUIEnvironment()->getRootGUIElement()->getElementFromId(id, true);
    if (elem)
        elem->remove();
}

bool SceneHandler::IsButtonPressed(unsigned int id)
{
    irr::gui::IGUIElement* elem = Graphics::GetGUIEnvironment()->getRootGUIElement()->getElementFromId(id, true);
    if (elem->getType() == irr::gui::EGUIET_BUTTON)
    {
        irr::gui::IGUIButton* button = dynamic_cast<irr::gui::IGUIButton*>(elem);
        if (button->isPressed())
            return true;
    }

    return false;
}

irr::core::vector3df SceneHandler::GetWorldCoordFromScreen()
{
    irr::core::vector2di screenPos = Input::GetInputHandler().MouseState.pos;
    irr::scene::ICameraSceneNode* cam = Graphics::GetSceneManager()->getActiveCamera();

    // Ray between the camera position and the far plane of the frustum
    irr::core::line3df ray = Graphics::GetCollisionManager()->getRayFromScreenCoordinates(screenPos, cam);

    // Plane in origo facing the camera
    irr::core::plane3d<irr::f32> plane({ 0,0,0 }, { 0,-1,0 });

    irr::core::vector3df intersectPoint;

    // Check where the ray intersect with the plane
    plane.getIntersectionWithLine(ray.start, ray.getVector(), intersectPoint);

    return intersectPoint;
}

void SceneHandler::AddGridSystem(const irr::core::dimension2du& dimension)
{
    irr::scene::IMesh* mesh = Graphics::GetGeometryCreator()->createPlaneMesh(DEFAULT_TILE_SIZE, dimension);
    irr::scene::ISceneNode* node = Graphics::GetSceneManager()->addMeshSceneNode(mesh);
    irr::core::vector2df gridPos;
   
    // Even width
    if (dimension.Width % 2 == 0)
        gridPos.X = DEFAULT_TILE_SIZE.X / 2.f;
    // Even height
    if (dimension.Height % 2 == 0)
        gridPos.Y = DEFAULT_TILE_SIZE.Y / 2.f;

    // Align it to be in the background
    node->setPosition({ gridPos.X, -10, gridPos.Y });
    
    // Change color of the mesh
    Graphics::GetSceneManager()->getMeshManipulator()->setVertexColors(mesh, irr::video::SColor(255, 0, 255, 0));

    node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
    node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_WIREFRAME, true);
    
}

irr::core::vector3df SceneHandler::SnapToGrid()
{
    irr::core::vector3df position = Get().GetWorldCoordFromScreen();
   
    position.X = std::round(position.X / DEFAULT_TILE_SIZE.X) * DEFAULT_TILE_SIZE.X;
    position.Z = std::round(position.Z / DEFAULT_TILE_SIZE.Y) * DEFAULT_TILE_SIZE.Y;

    return position;
}

int SceneHandler::RayHitObject()
{
	irr::core::vector2di screenPos = Input::GetInputHandler().MouseState.pos;
	irr::scene::ICameraSceneNode* cam = Graphics::GetSceneManager()->getActiveCamera();

	// Ray between the camera position and the far plane of the frustum
	irr::core::line3df ray = Graphics::GetCollisionManager()->getRayFromScreenCoordinates(screenPos, cam);

	for (int i = 0; i < Get().m_sprites.size(); i++)
	{
		Sprite* sprite = Get().m_sprites[i].get();
		if (sprite)
		{
			irr::f64 dist = 0;
			ray.getIntersectionWithSphere(sprite->GetPosition(), sprite->GetCollisionRadius(), dist);

			if (dist > 0)
			{
				//std::cout << "Dist: " << dist << "\n";
				return Get().m_sprites[i]->GetID();
			}
		}

		
	}

	return -1;
}
