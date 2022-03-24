#include "PCH.h"
#include "MenuScene.h"

/*
	[TODO] Add options if we got time
*/

void MenuScene::Load()
{
	Graphics::GetSceneManager()->setActiveCamera(m_defaultCamera);

	/*
		Load lua-script which builds up the menu?
	*/

	//Get Font
	std::string fontstr = FONTPATH + "roboto_28.xml";
	irr::gui::IGUIFont* font = Graphics::GetGUIEnvironment()->getFont(fontstr.c_str());

	// [Adjustable]
	irr::core::vector2di buttonSize = { 300, 100 };
	int verticalSpace = buttonSize.Y * 1.5;

	// [Not adjustable]
	irr::core::vector2di buttonHalfSize = { buttonSize.X / 2, buttonSize.Y / 2 };
	irr::core::vector2di centerPos		= { window_width / 2, window_height / 2};
	
	// [Adjustable]
	int yStart = centerPos.Y - verticalSpace;
	std::array<std::wstring, 3> buttonNames = { L"Play", L"Edit", L"Quit"};

	/*
		Title
	*/
	m_title = Graphics::GetGUIEnvironment()->addStaticText(
						L"Scripting project",
						irr::core::rect<irr::s32>(
						centerPos.X - 150,
						100,
						centerPos.X + 150,
						180), false,false);
	m_title->setOverrideFont(font);
	
	/*
		Buttons
	*/
	for (const auto& name : buttonNames)
	{
		irr::gui::IGUIButton* button = (Graphics::GetGUIEnvironment()->addButton
										(
										irr::core::rect<irr::s32>(
										centerPos.X - buttonHalfSize.X,
										yStart - buttonHalfSize.Y,
										centerPos.X + buttonHalfSize.X,
										yStart + buttonHalfSize.Y),
										0, -1, name.c_str()
										)
							);
		//Set font for this button
		button->setOverrideFont(font);

		yStart += verticalSpace;
		m_buttons.push_back(button);
	}
}

void MenuScene::Clean()
{
	//Remove all UI
	m_title->remove();

	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons.at(i)->remove();
}

void MenuScene::Update()
{
	//Play button
	if (m_buttons.at(0)->isPressed())
		SceneAccess::GetSceneHandler()->SetScene(EScene::Game);
	
	//Edit button
	else if (m_buttons.at(1)->isPressed())
		SceneAccess::GetSceneHandler()->SetScene(EScene::Editor);

	//Quit button
	else if (m_buttons.at(2)->isPressed())
		SceneAccess::GetSceneHandler()->SetScene(EScene::None);
}
