#pragma once
#include "Model.h"
#include "CppToLua.h"

class Scene
{
private:
	//Register? with ENTT?

protected:
	std::unordered_map<unsigned int, Model> m_models;
	irr::scene::ICameraSceneNode* m_camera;

public:
	Scene();
	virtual ~Scene();

	virtual void Load() = 0;
	virtual void Clean() = 0;
	virtual void Update() = 0;

	// Models
	unsigned int AddModel(std::string& file);
	void RemoveModel(unsigned int id);

	void UpdatePosition(unsigned int id, const irr::core::vector3df& pos);

	// Camera
	bool RemoveCamera();

};