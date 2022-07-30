#include "PCH.h"
#include "Element2D.h"
#include <utility>

Element2D::Element2D()
{
}

void Element2D::SetVisibility(const bool& set)
{
	m_visible = set;
}

Text::Text(std::string text)
{
	m_rect = irr::core::recti(0, 0, 1000, 500);
	m_color = irr::video::SColor(255);
	m_text = text;
}

void Text::SetRectangle(irr::core::recti rect)
{
	m_rect = rect;
}

void Text::SetColor(irr::video::SColor color)
{
	m_color = color;
}

void Text::Draw()
{
	Graphics2D::GetDefaultFont()->draw(irr::core::stringw(m_text.c_str()), m_rect, m_color);
}

void Text::Update(void* buff)
{
}

void Text::SetPosition(irr::core::recti pos)
{
}

Healthbar::Healthbar(const irr::core::rect<irr::s32>& pos)
{
	//m_foreground = pos;
	m_background = pos;
	m_backgroundColor = irr::video::SColor(255, 255, 0, 0);
	m_foregroundColor = irr::video::SColor(255, 0, 255, 0);
}

void Healthbar::SetMaxHealth(const float& maxHp)
{
	m_max = maxHp;
}

void Healthbar::SetBackgroundColor(const irr::video::SColor color)
{
	m_backgroundColor = color;
}

void Healthbar::SetForegroundColor(const irr::video::SColor color)
{
	m_foregroundColor = color;
}

void Healthbar::Draw()
{
	if (m_visible)
	{
		Graphics::GetDriver()->draw2DRectangle(m_backgroundColor, m_background);
		Graphics::GetDriver()->draw2DRectangle(m_foregroundColor, m_foreground);
	}
}

void Healthbar::Update(void* buff)
{
	m_current = *(float*)buff;

	float scale = std::min((m_current / m_max), 1.0f);
	irr::s32 width = m_background.getWidth();
	m_foreground.UpperLeftCorner = irr::core::vector2di(m_background.UpperLeftCorner.X , m_background.UpperLeftCorner.Y);
	m_foreground.LowerRightCorner = irr::core::vector2di(static_cast<int>((m_background.LowerRightCorner.X - width) + width * scale), m_background.LowerRightCorner.Y);
}

void Healthbar::SetPosition(irr::core::recti pos)
{
	m_background = pos;
}

Image::Image(const std::string& filepath)
{
	m_texture = Graphics::GetDriver()->getTexture((SPRITEPATH + filepath).c_str());
}

Image::~Image()
{
}

void Image::SetImagePosition(const irr::core::vector2di& newPos)
{
	m_position = newPos;
}

void Image::SwitchImage(const std::string& filepath)
{
	m_texture = Graphics::GetDriver()->getTexture((SPRITEPATH + filepath).c_str());
}

void Image::SetSize(const float& size)
{
	m_size = size;
}

void Image::Draw()
{
	if (m_texture)
	{
		if (m_size > 0)
		{
			irr::core::recti rect = irr::core::recti(m_position.X, m_position.Y, m_position.X + m_size, m_position.Y + m_size);
			Graphics::GetDriver()->draw2DImage(m_texture, rect, rect);
		}
		else
			Graphics::GetDriver()->draw2DImage(m_texture, m_position);
	}
}

void Image::Update(void* buff)
{
}

void Image::SetPosition(irr::core::recti pos)
{
}
