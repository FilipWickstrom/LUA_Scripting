#pragma once

class Sprite
{
private:
	irr::scene::ISceneNode* m_node;

public:
	Sprite();
	Sprite(const std::string& textureName);
	~Sprite() = default;

	void LoadTexture(const std::string& filename);
	void Remove();
	void SetVisible(const bool& isVisible = true);
	
	/*
		Transform
	*/
	void SetPosition(const irr::core::vector3df& pos);
	void SetRotation(const irr::core::vector3df& rot);
	void SetScale(const irr::core::vector3df& scl);
};
