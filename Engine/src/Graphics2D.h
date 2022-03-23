#pragma once
#include "Element2D.h"

class Graphics2D
{
private:

	Graphics2D();
	~Graphics2D();

	irr::video::IVideoDriver* m_driver = nullptr;
	irr::gui::IGUIFont* m_defaultFont = nullptr;

	std::unordered_map<unsigned int, Element2D*> m_elements;

public:

	static auto& Get();
	static irr::gui::IGUIFont* GetDefaultFont();

	static void Draw();

};