#pragma once
#include "Element2D.h"

class Graphics2D
{
private:

	Graphics2D();
	~Graphics2D();

	irr::video::IVideoDriver* m_driver = nullptr;
	irr::gui::IGUIFont* m_defaultFont = nullptr;

	unsigned int m_nextID = 0;
	bool m_shouldRender = true;

	std::unordered_map<unsigned int, Element2D*> m_elements;
	std::vector<Element2D*> m_copyElements;

public:

	static auto& Get();
	static irr::gui::IGUIFont* GetDefaultFont();
	static Element2D* GetElement(const unsigned int& index);

	static const unsigned int AddHealthbar(irr::core::rect<irr::s32> pos);
	static const unsigned int Add2dImage(const std::string& filepath, irr::core::vector2di pos);

	// Update healthbar pos
	static void SetPosition(const unsigned int& index, irr::core::rect<irr::s32> pos);

	// update 2d image pos
	static void SetPosition(const unsigned int& index, irr::core::vector2di pos);

	static void ChangeImage2D(const unsigned int& index, const std::string& filepath);

	static void RemoveElement(const unsigned int& index);

	static void SetSizeImage2D(const unsigned int& index, const float& size);

	// true - will render UI, false - won't render UI
	static void ToggleRender(const bool& toggle);

	static void Draw();
	static void AlwaysDraw();
	static void RemoveAll();

};