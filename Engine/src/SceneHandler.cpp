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
        Cleaning up in LUA
    */
    lua_getglobal(LUA, "Clean");
    LuaHandler::CheckErrors(0, 0);

    /*
        Cleaning up in C++
    */
    Graphics::GetSceneManager()->clear();
    Graphics::GetSceneManager()->getMeshCache()->clear();
    Graphics::GetGUIEnvironment()->clear();

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
        return true;
    }
    return false;
}

unsigned int SceneHandler::AddSprite(const std::string& file)
{
    unsigned int id = Get().m_spriteUID++;
    Get().m_sprites.emplace(id, std::make_unique<Sprite>(file));
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

bool SceneHandler::CheckSpriteCollision(const unsigned int& firstObjID, const unsigned int& secondObjID)
{
    if (Get().m_sprites.find(firstObjID) != Get().m_sprites.end() &&
        Get().m_sprites.find(secondObjID) != Get().m_sprites.end())
    {

        Sprite* first = Get().m_sprites.at(firstObjID).get();
        Sprite* second = Get().m_sprites.at(secondObjID).get();

        // Return false if one of them has collision enabled.
        if (!first->HasCollision() || !second->HasCollision())
            return false;

        //Collision check between rectangles - AABB
        //[OPTIMIZE] do sphere collision first before AABB
        const auto& rect1 = first->GetBounds();
        const auto& rect2 = second->GetBounds();

        return rect1.isRectCollided(rect2);
    }
    return false;
}

Sprite* SceneHandler::GetSprite(const unsigned int& id)
{
    if (Get().m_sprites.find(id) != Get().m_sprites.end())
    {
        return Get().m_sprites.at(id).get();
    }

    return nullptr;
}

void SceneHandler::AddCamera()
{
    //Add a default camera
    Get().m_camera = Graphics::GetSceneManager()->addCameraSceneNode();
    Graphics::GetSceneManager()->setActiveCamera(Get().m_camera);

    float aspectRatio = static_cast<float>(Graphics::GetWindowWidth()) /
                        static_cast<float>(Graphics::GetWindowHeight());
    float fov = 50.f;

    irr::core::matrix4 matrix;
    matrix.buildProjectionMatrixOrthoLH(fov * aspectRatio, fov, 0.1f, 500.f);

    Get().m_camera->setProjectionMatrix(matrix, true);
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

void SceneHandler::SetCameraFOV(const float& fov)
{
    if (!Get().m_camera) return;

    float thefov = fov;
    //Fov should not go below 0
    if (fov <= 0.f)
        thefov = 1.f;

    Get().m_camera->setFOV(irr::core::degToRad(thefov));
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

irr::core::line3df SceneHandler::GetRayFromScreenCoords(irr::core::vector2di screenCoords)
{
    irr::core::line3df ray;

    //Camera does not exist
    if (!Get().m_camera) return ray;

    return Graphics::GetSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates(screenCoords, Get().m_camera);
}


