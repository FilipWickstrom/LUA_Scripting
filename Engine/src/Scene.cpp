#include "PCH.h"
#include "Scene.h"

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
	m_models.clear();
}

unsigned int Scene::AddModel(std::string& file)
{
	static unsigned int modelCounter = 0;
	unsigned int id = modelCounter;
	modelCounter++;
	m_models.emplace(id, std::make_unique<Model>(file));
	return id;
}

void Scene::RemoveModel(unsigned int id)
{
	if (m_models.find(id) != m_models.end())
	{
		m_models.at(id)->Drop();
		m_models.erase(id);
	}
}

const irr::scene::ICameraSceneNode* Scene::GetCamera() const
{
	return Graphics::GetSceneManager()->getActiveCamera();
}

void Scene::UpdatePosition(unsigned int id, const irr::core::vector3df& pos)
{
	if(m_models.find(id) != m_models.end())
		m_models.at(id)->SetPosition(pos);
}

void Scene::SetModelScale(unsigned int id, const float& scale)
{
	if (m_models.find(id) != m_models.end())
		m_models.at(id)->SetScale(scale);
}

bool Scene::RemoveActiveCam()
{
	bool removed = false;
	irr::scene::ICameraSceneNode* oldCam = Graphics::GetSceneManager()->getActiveCamera();
	if (oldCam)
	{
		Graphics::GetSceneManager()->setActiveCamera(0);
		oldCam->remove();
		removed = true;
	}
	return removed;
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

	//Center text
	irrText->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	
	//Set an ID for the GUI
	unsigned int id = s_GUI_ID++;
	irrText->setID(id);

	std::string fontstr = FONTPATH + font;
	irr::gui::IGUIFont* irrfont = Graphics::GetGUIEnvironment()->getFont(fontstr.c_str());
	if (irrfont)
		irrText->setOverrideFont(irrfont);

	return id;
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
