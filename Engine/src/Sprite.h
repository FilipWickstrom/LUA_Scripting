#pragma once

class Sprite
{
private:
	irr::scene::ISceneNode* m_node;

public:
	Sprite();
	Sprite(const std::string& textureName);
	~Sprite();

	void LoadTexture(const std::string& filename);
	
	/*
		Transform
	*/
	void SetPosition(const irr::core::vector3df& pos);
	void SetRotation(const irr::core::vector3df& rot);
	void SetScale(const irr::core::vector3df& scl);
	
	//drop? 
};
