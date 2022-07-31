#pragma once


class Element2D
{
protected:

	bool m_visible = true;

public:

	Element2D();
	virtual ~Element2D() = 0 {};

	virtual void Draw() = 0;
	virtual void Update(void* buff) = 0;
	virtual void SetPosition(irr::core::recti pos) = 0;
	void SetVisibility(const bool& set);
};

class Text : public Element2D
{
private:

	std::string m_text;
	irr::core::recti m_rect;
	irr::video::SColor m_color;

public:

	Text(std::string text);
	~Text() = default;

	void SetRectangle(irr::core::recti rect);
	void SetColor(irr::video::SColor color);

	// Inherited via Element2D
	virtual void Draw() override;

	// Inherited via Element2D
	virtual void Update(void* buff) override;

	// Inherited via Element2D
	virtual void SetPosition(irr::core::recti pos) override;
};

class Healthbar : public Element2D
{
private:

	irr::core::rect<irr::s32> m_foreground;
	irr::video::SColor m_foregroundColor;
	irr::core::rect<irr::s32> m_background;
	irr::video::SColor m_backgroundColor;
	float m_max = 100;
	float m_current = 100;

public:

	Healthbar(const irr::core::rect<irr::s32>& pos);
	~Healthbar() = default;
	void SetMaxHealth(const float& maxHp);
	void SetBackgroundColor(const irr::video::SColor color);
	void SetForegroundColor(const irr::video::SColor color);

	// Inherited via Element2D
	virtual void Draw() override;

	// Inherited via Element2D
	virtual void Update(void* buff) override;

	// Inherited via Element2D
	virtual void SetPosition(irr::core::recti pos) override;

};
