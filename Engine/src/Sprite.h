#pragma once

class Sprite
{
private:
	irr::scene::ISceneNode*				m_node;
	irr::scene::IMesh*					m_mesh;
	irr::video::ITexture*				m_texture;
	irr::core::vector2df				m_size;
	float								m_collisionRadius;
	bool								m_hasCollision;
	irr::scene::ISceneNodeAnimator*		m_blinkEffect;

public:
	Sprite();
	Sprite(const std::string& textureName);
	~Sprite() = default;

	void LoadTexture(const std::string& filename = "");
	void Remove();
	void SetVisible(const bool& isVisible = true);
	void SetCollision(const bool& hasCollision = true);
	const bool& HasCollision() const;
	void SetColliderSize(const float& width, const float& height);
	
	/*
		Transform
	*/
	void SetPosition(const irr::core::vector3df& pos);
	void SetRotation(const irr::core::vector3df& rot);
	void SetScale(const irr::core::vector3df& scl);
	irr::core::matrix4 GetAbsoluteTransform();

	/*
		Getters
	*/
	const irr::core::vector3df& GetPosition() const;
	//Only X and Z
	const irr::core::vector2df GetPosition2D() const; 
	const float& GetCollisionRadius() const;

	//Get the rectangle around the sprite
	const irr::core::rectf GetBounds() const;

	// Blinking animator
	void EnableBlinkEffect(bool toggle = true);
};
