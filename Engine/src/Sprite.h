#pragma once

class Sprite
{
private:
	irr::scene::ISceneNode* m_node;
	irr::core::vector2df	m_size;
	bool					m_collision = true;

public:
	Sprite();
	Sprite(const std::string& textureName);
	~Sprite() = default;

	void LoadTexture(const std::string& filename);
	void Remove();
	void SetVisible(const bool& isVisible = true);
	void SetCollision(const bool& hasCollision = true);
	const bool& HasCollision() const;
	
	/*
		Transform
	*/
	void SetPosition(const irr::core::vector3df& pos);
	void SetRotation(const irr::core::vector3df& rot);
	void SetScale(const irr::core::vector3df& scl);

	//Get the rectangle around the sprite
	const irr::core::rectf GetBounds() const;
};
