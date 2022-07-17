#include "PCH.h"
#include "Graphics2D.h"

#define INSTANCE Graphics2D::Get()

Graphics2D::Graphics2D()
{
    m_driver = Graphics::GetDriver();
    m_defaultFont = Graphics::GetGUIEnvironment()->getBuiltInFont();

    //Healthbar* test = new Healthbar(irr::core::rect<irr::s32>(0, 0, 1000, 100));
    //m_elements[0] = test;
    //float t = 50.0f;
    //test->Update(&t);
    //t = 100;
    //test->Update(&t);
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

Element2D* Graphics2D::GetElement(const unsigned int& index)
{
    if(INSTANCE.m_elements.find(index) != INSTANCE.m_elements.end())
        return INSTANCE.m_elements.at(index);

    return nullptr;
}

const unsigned int Graphics2D::AddHealthbar(irr::core::rect<irr::s32> pos)
{
    Healthbar* newH = new Healthbar(pos);
    INSTANCE.m_elements[INSTANCE.m_nextID] = newH;
    const unsigned int ret = INSTANCE.m_nextID;
    INSTANCE.m_nextID++;
    return ret;
}

void Graphics2D::SetPosition(const unsigned int& index, irr::core::rect<irr::s32> pos)
{
    if (INSTANCE.m_elements.find(index) != INSTANCE.m_elements.end())
    {
        INSTANCE.m_elements.at(index)->SetPosition(pos);
    }
}

void Graphics2D::RemoveElement(const unsigned int& index)
{
    INSTANCE.m_elements.erase(index);
}

void Graphics2D::ToggleRender(const bool& toggle)
{
	INSTANCE.m_shouldRender = toggle;
}

void Graphics2D::Draw()
{
    if (INSTANCE.m_driver && INSTANCE.m_shouldRender)
    {
        for (auto elem : INSTANCE.m_elements)
        {
            elem.second->Draw();
        }
    }
}

void Graphics2D::RemoveAll()
{
    Get().m_nextID = 0;
    Get().m_elements.clear();
}
