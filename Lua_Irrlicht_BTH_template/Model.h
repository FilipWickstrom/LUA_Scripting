#pragma once
#include "Object.h"
#include <string>

class Model: public Object
{
private:

	irr::scene::ISceneNode* m_node;

	// This could potentially be used with the script to identify which model is linked to which table.
	unsigned int m_id = 0;

	void LoadMesh(std::string& meshName);

public:

	Model(std::string& meshName);
	Model(std::string& meshName, irr::core::vector3df pos,
		irr::core::vector3df rot, irr::core::vector3df scale);

	void SetID(unsigned int id);
	const unsigned int& GetID() const;

	void Update();
};