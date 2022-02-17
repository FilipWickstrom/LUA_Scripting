#pragma once
#include <vector>
#include "Model.h"

class Scene
{
private:

	std::vector<Model> m_models;

public:

	Scene();
	~Scene();

	// Adds an object with an attached model.
	void AddObject(std::string modelPath, irr::core::vector3df pos,
		irr::core::vector3df rot, irr::core::vector3df scale);

	// Loop through all models and update them.
	void Update();
};