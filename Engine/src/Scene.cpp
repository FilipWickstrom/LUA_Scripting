#include "PCH.h"
#include "Scene.h"

Scene::Scene()
{
	m_camera.Setup();
}

Scene::~Scene()
{

}

void Scene::AddBasicEnemy(float x, float y)
{
	/*
		Spawn an enemy in lua and an object to respresent it in game.
	*/
	m_enemyManager.NewBasicEnemy(x, y);
	this->AddObject("cube.obj", { x, 0.0f, y }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
	EnemyManager::m_freeIndex++;
}

void Scene::AddObject(std::string modelPath, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df scale)
{
	m_models[EnemyManager::m_freeIndex] = new Model(modelPath, pos, rot, scale, EnemyManager::m_freeIndex);
}

void Scene::Update()
{
	for (auto& model : m_models)
		model.second->Update();
}

void Scene::SetActive()
{
	m_camera.SetActive();
}