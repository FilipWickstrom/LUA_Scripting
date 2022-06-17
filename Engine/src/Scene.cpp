#include "PCH.h"
#include "Scene.h"

unsigned int Scene::s_Sprite_ID = 0;
unsigned int Scene::s_GUI_ID = 0;

Scene::Scene()
{
	m_camera = Graphics::GetSceneManager()->addCameraSceneNode();
	Graphics::GetSceneManager()->setActiveCamera(m_camera);
}

Scene::~Scene()
{
	//Clearing up the scene and gui in Irrlicht 
	Graphics::GetSceneManager()->clear();
	Graphics::GetSceneManager()->getMeshCache()->clear();
	Graphics::GetGUIEnvironment()->clear();
	//All nodes are gone now
	m_sprites.clear();

	//Reseting id's
	s_Sprite_ID = 0;
	s_GUI_ID = 0;

	//Removing active camera
	irr::scene::ICameraSceneNode* oldCam = Graphics::GetSceneManager()->getActiveCamera();
	if (oldCam)
	{
		Graphics::GetSceneManager()->setActiveCamera(0);
		oldCam->remove();
	}
}

unsigned int Scene::AddSprite(const std::string& file)
{
	unsigned int id = s_Sprite_ID++;
	m_sprites.emplace(id, std::make_unique<Sprite>(file));
	return id;
}

void Scene::RemoveSprite(const unsigned int& id)
{
	if (m_sprites.find(id) != m_sprites.end())
		m_sprites.erase(id);
}

void Scene::AddCamera()
{
	//Add a default camera
	m_camera = Graphics::GetSceneManager()->addCameraSceneNode();
	Graphics::GetSceneManager()->setActiveCamera(m_camera);

	float aspectRatio = static_cast<float>(Graphics::GetWindowWidth()) /
						static_cast<float>(Graphics::GetWindowHeight());
	float fov = 50.f;

	irr::core::matrix4 matrix;
	matrix.buildProjectionMatrixOrthoLH(fov * aspectRatio, fov, 0.1f, 500.f);

	m_camera->setProjectionMatrix(matrix, true);
}

void Scene::SetCameraPosition(const irr::core::vector3df& pos)
{
	if (m_camera)
		m_camera->setPosition(pos);
}

void Scene::SetCameraTarget(const irr::core::vector3df& tar)
{
	if (m_camera)
		m_camera->setTarget(tar);
}

void Scene::SetCameraFOV(const float& fov)
{
	if (!m_camera) return;

	float thefov = fov;
	//Fov should not go below 0
	if (fov <= 0.f)
		thefov = 1.f;

	m_camera->setFOV(irr::core::degToRad(thefov));
}

void Scene::SetSpritePosition(const unsigned int& id, const irr::core::vector3df& pos)
{
	if(m_sprites.find(id) != m_sprites.end())
		m_sprites.at(id)->SetPosition(pos);
}

void Scene::SetSpriteScale(const unsigned int& id, const irr::core::vector3df& scl)
{
	if (m_sprites.find(id) != m_sprites.end())
		m_sprites.at(id)->SetScale(scl);
}

void Scene::SetSpriteRotation(const unsigned int& id, const irr::core::vector3df& rot)
{
	if (m_sprites.find(id) != m_sprites.end())
		m_sprites.at(id)->SetRotation(rot);
}

unsigned int Scene::AddText(const std::string& text, const std::string& font, irr::core::vector2di pos, irr::core::vector2di size)
{
	std::wstring wstring(text.begin(), text.end());
	irr::gui::IGUIStaticText* irrText = Graphics::GetGUIEnvironment()->addStaticText
										(
										wstring.c_str(),
										irr::core::rect<irr::s32>(
										pos.X - (size.X/2),
										pos.Y - (size.Y/2),
										pos.X + (size.X/2),
										pos.Y + (size.Y/2)),
										false, false
										);
#if DEBUG_UI
	irrText->setDrawBackground(true);
#endif

	//Center text
	irrText->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	
	//Set an ID for the GUI
	unsigned int id = s_GUI_ID++;
	irrText->setID(id);

	std::string fontstr = FONTPATH + font;
	irr::gui::IGUIFont* irrfont = Graphics::GetGUIEnvironment()->getFont(fontstr.c_str());
	if (irrfont)
		irrText->setOverrideFont(irrfont);

	m_texts[id] = irrText;

	return id;
}

void Scene::UpdateText(unsigned int& id, const std::string& text)
{
	std::wstring widestr = std::wstring(text.begin(), text.end());
	m_texts[id]->setText(widestr.c_str());
}

unsigned int Scene::AddButton(const std::string& text, const std::string& font, irr::core::vector2di pos, irr::core::vector2di size)
{
	std::wstring wstring(text.begin(), text.end());
	irr::gui::IGUIButton* irrButton = Graphics::GetGUIEnvironment()->addButton
										(
										irr::core::rect<irr::s32>(
										pos.X - (size.X/2),
										pos.Y - (size.Y/2),
										pos.X + (size.X/2),
										pos.Y + (size.Y/2)),
										0, -1, wstring.c_str()
										);

	//Set an ID for the GUI
	unsigned int id = s_GUI_ID++;
	irrButton->setID(id);

	std::string fontstr = FONTPATH + font;
	irr::gui::IGUIFont* irrfont = Graphics::GetGUIEnvironment()->getFont(fontstr.c_str());
	if (irrfont)
		irrButton->setOverrideFont(irrfont);

	return id;
}

void Scene::RemoveGUI(unsigned int id)
{
	irr::gui::IGUIElement* elem = Graphics::GetGUIEnvironment()->getRootGUIElement()->getElementFromId(id, true);
	if (elem)
		elem->remove();
}

bool Scene::IsButtonPressed(unsigned int id)
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
