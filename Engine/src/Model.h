#pragma once
#include "Object.h"

class Model: public Object
{
private:

	irr::scene::ISceneNode* m_node = nullptr;

	// This could potentially be used with the script to identify which model is linked to which table.
	unsigned int m_id = 0;

	void LoadMesh(std::string& meshName);

public:

	Model() = default;
	Model(std::string& meshName);
	Model(std::string& meshName, irr::core::vector3df pos,
		irr::core::vector3df rot, irr::core::vector3df scale);

	Model(std::string& meshName, irr::core::vector3df pos,
		irr::core::vector3df rot, irr::core::vector3df scale,
		unsigned int& id);

	void SetID(unsigned int id);
	const unsigned int& GetID() const;

	void Update();

	void Drop();
};