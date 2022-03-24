#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
private:
	irr::gui::IGUIStaticText* m_title;
	std::vector<irr::gui::IGUIButton*> m_buttons;

public:
	MenuScene() = default;
	~MenuScene() = default;

	// Inherited via Scene
	virtual void Load() override;
	virtual void Clean() override;
	virtual void Update() override;
};