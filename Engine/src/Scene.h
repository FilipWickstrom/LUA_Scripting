#pragma once
#include "Model.h"
#include "CppToLua.h"

class Scene
{
protected:
	std::unordered_map<unsigned int, Model> m_models;
	irr::scene::ICameraSceneNode* m_defaultCamera;

public:
	Scene();
	virtual ~Scene();

	virtual void Load() = 0;
	virtual void Clean() = 0;
	virtual void Update() = 0;

	// Models
	unsigned int AddModel(std::string& file);
	void RemoveModel(unsigned int id);

	// Camera
	bool RemoveCamera();

};