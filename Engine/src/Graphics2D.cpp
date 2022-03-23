#include "PCH.h"
#include "Graphics2D.h"

#define INSTANCE Graphics2D::Get()

Graphics2D::Graphics2D()
{
    m_driver = Graphics::GetDriver();
    m_defaultFont = Graphics::GetGUIEnvironment()->getBuiltInFont();

    Healthbar* test = new Healthbar(irr::core::rect<irr::s32>(0, 0, 1000, 100));
    m_elements[0] = test;
}

Graphics2D::~Graphics2D()
{
    for (auto elem : m_elements)
        delete elem.second;
}

auto& Graphics2D::Get()
{
    static Graphics2D instance;
    return instance;
}

irr::gui::IGUIFont* Graphics2D::GetDefaultFont()
{
    return INSTANCE.m_defaultFont;
}

void Graphics2D::Draw()
{
    if (INSTANCE.m_driver)
    {
        for (auto elem : INSTANCE.m_elements)
        {
            elem.second->Draw();
        }
    }
}
