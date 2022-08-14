#include "PCH.h"
#include "SceneHandler.h"
#include "CppToLua.h"
//#include "CGUITTFont.h"

SceneHandler::SceneHandler()
{
    m_spriteUID     = 0;
    m_textUID       = 0;
    m_image2dUID    = 0;
    m_buttonUID     = 0;
    m_camera        = nullptr;
    m_gridsystem    = nullptr;
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

    m_spriteUID  = 0;
    m_textUID    = 0;
    m_image2dUID = 0;

    m_sprites.clear();
    m_texts.clear();
    m_image2ds.clear();

    //Removing active camera
    irr::scene::ICameraSceneNode* oldCam = Graphics::GetSceneManager()->getActiveCamera();
    if (oldCam)
        oldCam->remove();
    
    Graphics::GetSceneManager()->setActiveCamera(0);
    m_camera = nullptr;

    // Reset grid and delete it if we got one
    if (m_gridsystem.get())
        m_gridsystem.reset();
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

Sprite* SceneHandler::GetSprite(const unsigned int& id)
{
    Sprite* toReturn = nullptr;

    if (Get().m_sprites.find(id) != Get().m_sprites.end())
    {
        toReturn = Get().m_sprites.at(id).get();
    }

    return toReturn;
}

void SceneHandler::SetSpriteBlinking(const unsigned int& id, bool toggle)
{
    if (Get().m_sprites.find(id) != Get().m_sprites.end())
        Get().m_sprites.at(id)->EnableBlinkEffect(toggle);
}

void SceneHandler::SetColliderSize(const unsigned int& id, const float& width, const float& height)
{
    if (Get().m_sprites.find(id) != Get().m_sprites.end())
        Get().m_sprites.at(id)->SetColliderSize(width, height);
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
    matrix.buildProjectionMatrixOrthoLH(width, height, 1.f, 1000.f);

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
    matrix.buildProjectionMatrixOrthoLH(width / thezoom, height / thezoom, 1.f, 1000.f);

    Get().m_camera->setProjectionMatrix(matrix, true);
}

irr::scene::ICameraSceneNode* SceneHandler::GetCamera()
{
    return Get().m_camera;
}

unsigned int SceneHandler::AddText(const std::string& text)
{
    //Get an ID for the GUI
    unsigned int id = Get().m_textUID++;

    // Default values
    irr::core::vector2di pos = { 0,0 };
    irr::core::vector2di size = { 150, 50 };

    std::wstring wtext(text.begin(), text.end());

    irr::gui::IGUIStaticText* irrText = Graphics::GetGUIEnvironment()->addStaticText
    (
        wtext.c_str(),
        irr::core::recti(pos.X,
                         pos.Y,
                         pos.X + size.X,
                         pos.Y + size.Y),
        0, id
    );
    Get().m_texts[id] = irrText;

#if DEBUG_UI
    irrText->setDrawBackground(true);
#endif

    irrText->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
    irrText->setOverrideColor(irr::video::SColor(255, 255, 255, 255));

//    std::wstring wstring(text.begin(), text.end());
//    irr::gui::IGUIStaticText* irrText = Graphics::GetGUIEnvironment()->addStaticText
//    (
//        wstring.c_str(),
//        irr::core::rect<irr::s32>(
//            pos.X - (size.X / 2),
//            pos.Y - (size.Y / 2),
//            pos.X + (size.X / 2),
//            pos.Y + (size.Y / 2)),
//        false, false
//    );
//#if DEBUG_UI
//    irrText->setDrawBorder(true);
//#endif
//
//    //Set color of the text to white
//    irrText->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
//    //Center text by default
//    irrText->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
//
//    //Set an ID for the GUI
//    unsigned int id = Get().m_textUID++;
//    irrText->setID(id);
//
//    std::string fontstr = FONTPATH + font;
//    irr::gui::IGUIFont* irrfont = Graphics::GetGUIEnvironment()->getFont(fontstr.c_str());
//    if (irrfont)
//        irrText->setOverrideFont(irrfont);
//
//    Get().m_texts[id] = irrText;

    return id;
}

void SceneHandler::SetTextPosition(const unsigned int& id, const irr::core::vector2di& pos)
{
    if (Get().m_texts.find(id) != Get().m_texts.end())
        Get().m_texts.at(id)->setRelativePosition(pos);
}

void SceneHandler::SetTextSize(const unsigned int& id, const irr::core::vector2d<irr::u32>& size)
{
    if (Get().m_texts.find(id) != Get().m_texts.end())
    {
        irr::gui::IGUIStaticText* text = Get().m_texts.at(id);
        text->setMinSize(size);
        text->setMaxSize(size);

        // Change font size to fit with the textfield
        irr::gui::IGUIFont* irrfont = nullptr;
        
        /*
            Get a font that fits with the text
        */
        // Load in font that fits with the button size
        std::array<std::string, 4> fontnames = { "small.xml", "medium.xml", "large.xml", "huge.xml" };
        for (int i = 0; i < fontnames.size(); i++)
        {
            irr::gui::IGUIFont* tempfont = Graphics::GetGUIEnvironment()->getFont((FONTPATH + fontnames.at(i)).c_str());
            if (tempfont)
            {
                irr::core::dimension2du dimension = tempfont->getDimension(text->getText());

                // Check to see that we are not outside of the button
                if (dimension.Width < (irr::u32)size.X && dimension.Height < (irr::u32)size.Y)
                    irrfont = tempfont;

                // Has reached over limit - end here
                else
                    break;
            }
        }

        text->setOverrideFont(irrfont);
    }
}

void SceneHandler::SetTextAlignment(const unsigned int& id, const irr::gui::EGUI_ALIGNMENT& alignment)
{
    if (Get().m_texts.find(id) != Get().m_texts.end())
        Get().m_texts.at(id)->setTextAlignment(alignment, irr::gui::EGUIA_CENTER);
}

void SceneHandler::UpdateText(const unsigned int& id, const std::string& text)
{
    if (Get().m_texts.find(id) != Get().m_texts.end())
    {
        std::wstring widestr = std::wstring(text.begin(), text.end());
        Get().m_texts.at(id)->setText(widestr.c_str());
    }
}

void SceneHandler::SetTextFont(const unsigned int& id, const std::string& fontname)
{
    if (Get().m_texts.find(id) != Get().m_texts.end())
    {
        irr::gui::IGUIFont* font = Graphics::GetGUIEnvironment()->getFont((FONTPATH + fontname).c_str());
        if (font)
           Get().m_texts.at(id)->setOverrideFont(font);
    }
}

unsigned int SceneHandler::AddButton()
{
    //Get an ID for the GUI
    unsigned int id = Get().m_buttonUID++;

    // Default values
    irr::core::vector2di pos = { 0,0 };
    irr::core::vector2di size = { 150, 100 };

    irr::gui::IGUIButton* irrButton = Graphics::GetGUIEnvironment()->addButton
    (
        irr::core::recti(pos.X,
                         pos.Y,
                         pos.X + size.X,
                         pos.Y + size.Y),
                         0, id
    );
    irrButton->setDrawBorder(true);
    Get().m_buttons[id] = irrButton;

    return id;
}

void SceneHandler::RemoveButton(const unsigned int& id)
{
    if (Get().m_buttons.find(id) != Get().m_buttons.end())
    {
        Get().m_buttons.at(id)->remove();
        Get().m_buttons.erase(id);
    }
}

bool SceneHandler::IsButtonPressed(const unsigned int& id)
{
    if (Get().m_buttons.find(id) != Get().m_buttons.end())
    {
        return Get().m_buttons.at(id)->isPressed();
    }
    return false;
}

void SceneHandler::SetButtonText(const unsigned int& id, const std::string& text)
{
    if (Get().m_buttons.find(id) != Get().m_buttons.end())
    {
        irr::gui::IGUIButton* button = Get().m_buttons.at(id);
        irr::gui::IGUIFont* irrfont = nullptr;
        std::wstring wtext(text.begin(), text.end());
        irr::core::vector2di size = button->getAbsoluteClippingRect().getSize();

        /*
            Get a font that fits with the text
        */
        // Load in font that fits with the button size
        std::array<std::string, 4> fontnames = { "small.xml", "medium.xml", "large.xml", "huge.xml" };
        for (int i = 0; i < fontnames.size(); i++)
        {
            irr::gui::IGUIFont* tempfont = Graphics::GetGUIEnvironment()->getFont((FONTPATH + fontnames.at(i)).c_str());
            if (tempfont)
            {
                irr::core::dimension2du dimension = tempfont->getDimension(wtext.c_str());

                // Check to see that we are not outside of the button
                if (dimension.Width < (irr::u32)size.X && dimension.Height < (irr::u32)size.Y)
                    irrfont = tempfont;

                // Has reached over limit - end here
                else
                    break;
            }
        }

        /*
            Add a text
        */
        // Text get id 0 for this button
        irr::gui::IGUIStaticText* irrText = Graphics::GetGUIEnvironment()->addStaticText(wtext.c_str(),
                                            irr::core::recti(0, 0, size.X, size.Y),
                                            false, false, button, 0);

        irrText->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
        irrText->setOverrideFont(irrfont);
        irrText->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    }
}

void SceneHandler::SetButtonFont(const unsigned int& id, const std::string& fontname)
{
    if (Get().m_buttons.find(id) != Get().m_buttons.end())
    {
        irr::gui::IGUIButton* button = Get().m_buttons.at(id);

        irr::gui::IGUIFont* irrfont = Graphics::GetGUIEnvironment()->getFont((FONTPATH + fontname).c_str());
        if (irrfont)
        {
            // Text is always placed at id 0 at the button
            irr::gui::IGUIElement* guielem = button->getElementFromId(0);
            if (guielem)
            {
                irr::gui::IGUIStaticText* text = static_cast<irr::gui::IGUIStaticText*>(guielem);
                
                // Adjust the text
                text->setOverrideFont(irrfont);
            }
        }
    }
}

void SceneHandler::SetButtonPosition(const unsigned int& id, const irr::core::vector2di& pos)
{
    if (Get().m_buttons.find(id) != Get().m_buttons.end())
    {
        irr::gui::IGUIButton* button = Get().m_buttons.at(id);
        button->setRelativePosition(pos);
    }
}

void SceneHandler::SetButtonSize(const unsigned int& id, const irr::core::vector2d<irr::u32> size)
{
    if (Get().m_buttons.find(id) != Get().m_buttons.end())
    {
        irr::gui::IGUIButton* button = Get().m_buttons.at(id);
        button->setMinSize(size);
        button->setMaxSize(size);
    }
}

void SceneHandler::SetButtonImage(const unsigned int& id, const std::string& filename)
{
    if (Get().m_buttons.find(id) != Get().m_buttons.end())
    {
        //Get button and some information about it
        irr::gui::IGUIButton* button = Get().m_buttons.at(id);
        irr::core::vector2di buttonSize(button->getAbsoluteClippingRect().getWidth(),
                                        button->getAbsoluteClippingRect().getHeight());

        // Get texture and calculate the aspectRatio
        irr::video::ITexture* texture = Graphics::GetDriver()->getTexture((SPRITEPATH + filename).c_str());
        irr::core::vector2df textureSize(static_cast<irr::f32>(texture->getSize().Width),
                                         static_cast<irr::f32>(texture->getSize().Height));
        float aspectRatio = textureSize.X / textureSize.Y;

        // Size of the image inside of the button 
        // Maximize in Height
        irr::core::dimension2du imageDimension(static_cast<irr::u32>(buttonSize.Y * aspectRatio),
                                               static_cast<irr::u32>(buttonSize.Y));

        // Add and adjust the image
        // Image has id 1 for the parent
        irr::gui::IGUIImage* image = Graphics::GetGUIEnvironment()->addImage(texture, { 0,0 }, true, button, 1);
        image->setRelativePosition({ (buttonSize.X / 2) - static_cast<irr::s32>(imageDimension.Width / 2), 0 });
        image->setMinSize(imageDimension);
        image->setScaleImage(true);

        // Image is in the background
        button->sendToBack(image);

        // Adjust the text to be at top of the button
        irr::gui::IGUIElement* guielem = button->getElementFromId(0);
        if (guielem)
        {
            irr::gui::IGUIStaticText* text = static_cast<irr::gui::IGUIStaticText*>(guielem);
            text->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_UPPERLEFT);

            // [TODO] Check if texture is light or dark and change text color to the opposite.
        }
    }
}

const unsigned int SceneHandler::AddImage2d(const std::string& filepath)
{
    irr::video::ITexture* texture = Graphics::GetDriver()->getTexture((SPRITEPATH + filepath).c_str());
    irr::gui::IGUIImage* image = Graphics::GetGUIEnvironment()->addImage(texture, { 0,0 });
    image->setScaleImage(true);

    unsigned int id = Get().m_image2dUID++;
    image->setID(id);

    Get().m_image2ds[id] = image;

    return id;
}

void SceneHandler::RemoveImage2d(const unsigned int& index)
{
    if (Get().m_image2ds.find(index) != Get().m_image2ds.end())
    {
        Get().m_image2ds.at(index)->remove();
        Get().m_image2ds.erase(index);
    }
}

void SceneHandler::ChangeImage2d(const unsigned int& index, const std::string& filepath)
{
    if (Get().m_image2ds.find(index) != Get().m_image2ds.end())
    {
        irr::core::recti rect = Get().m_image2ds.at(index)->getRelativePosition();
        irr::core::vector2di pos = { rect.UpperLeftCorner.X, rect.UpperLeftCorner.Y };

        Get().m_image2ds.at(index)->remove();

        irr::video::ITexture* texture = Graphics::GetDriver()->getTexture((SPRITEPATH + filepath).c_str());
        irr::gui::IGUIImage* image = Graphics::GetGUIEnvironment()->addImage(texture, pos);
        image->setScaleImage(true);
        Get().m_image2ds[index] = image;
    }
}

void SceneHandler::SetImage2dPosition(const unsigned int& index, irr::core::vector2di pos)
{
    if (Get().m_image2ds.find(index) != Get().m_image2ds.end())
        Get().m_image2ds.at(index)->setRelativePosition(pos);
}

void SceneHandler::SetImage2dScale(const unsigned int& index, const float& scale)
{
    if (Get().m_image2ds.find(index) != Get().m_image2ds.end())
    {
        irr::core::dimension2du dimension = Get().m_image2ds.at(index)->getImage()->getOriginalSize();
        Get().m_image2ds.at(index)->setMinSize({ (irr::u32)(dimension.Width  * scale), 
                                                 (irr::u32)(dimension.Height * scale)});
    }
}

irr::core::vector3df SceneHandler::GetWorldCoordFromScreen()
{
    irr::core::vector2di screenPos = Graphics::GetDevice()->getCursorControl()->getPosition();
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

void SceneHandler::AddGridSystem(const irr::core::vector2di& size)
{
    // Grid does not exist - create a new!
    if (!Get().m_gridsystem.get())
        Get().m_gridsystem = std::make_unique<Gridsystem>(size);
    // Otherwise just change the size
    else
        Get().m_gridsystem->SetSize(size);
}

Gridsystem* SceneHandler::GetGridsystem()
{
    return Get().m_gridsystem.get();
}
