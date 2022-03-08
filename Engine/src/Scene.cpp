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

int Scene::AddModel(std::string modelPath)
{
	this->AddObject(modelPath, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, m_freeIndex);
	int ret = m_freeIndex;
	m_freeIndex++;
	return ret;
}

void Scene::RemoveModel(unsigned int index)
{
	m_models[index].Drop();
	m_models.erase(index);
}

void Scene::AddObject(std::string modelPath, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df scale)
{
	//m_models[EnemyManager::m_freeIndex] = Model(modelPath, pos, rot, scale, EnemyManager::m_freeIndex);
}

void Scene::AddObject(std::string modelPath, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df scale, unsigned int index)
{
	m_models[index] = Model(modelPath, pos, rot, scale, index);
}

void Scene::Update()
{
	for (auto& model : m_models)
		model.second.Update();
}

void Scene::SetActive()
{
	m_camera.SetActive();
}