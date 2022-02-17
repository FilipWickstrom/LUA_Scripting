#pragma once
#include "Object.h"
#include <string>

class Model: public Object
{
private:

	irr::scene::ISceneNode* m_node;
	unsigned int m_id;

	void LoadMesh(std::string& meshName);

public:

	Model(std::string& meshName);
	Model(std::string& meshName, irr::core::vector3df pos,
		irr::core::vector3df rot, irr::core::vector3df scale);

	void Update();
};