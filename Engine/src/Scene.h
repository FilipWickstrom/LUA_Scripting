#pragma once
#include "Model.h"
#include "Camera.h"
#include "EnemyManager.h"

class Scene
{
private:

	std::unordered_map<unsigned int, Model> m_models;

	// Lua manager for all enemies.
	EnemyManager m_enemyManager;
	unsigned int m_freeIndex = 0;

	// Adds an object with an attached model.
	void AddObject(std::string modelPath, irr::core::vector3df pos,
		irr::core::vector3df rot, irr::core::vector3df scale);

	void AddObject(std::string modelPath, irr::core::vector3df pos,
		irr::core::vector3df rot, irr::core::vector3df scale, unsigned int index);

	Camera m_camera;

public:

	Scene();
	~Scene();

	void AddBasicEnemy(float x, float y);

	int AddModel(std::string modelPath);
	void RemoveModel(unsigned int index);

	// Loop through all models and update them.
	void Update();
	void SetActive();
};