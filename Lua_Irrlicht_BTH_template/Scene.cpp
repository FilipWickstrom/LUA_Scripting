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
	m_enemyManager.NewBasicEnemy();
	this->AddObject("../Meshes/shitty_tree.obj", { x, 0.0f, y },
		{ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
}

void Scene::AddObject(std::string modelPath, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df scale)
{
	m_models.emplace(enemyId::s_freeIndex, Model(modelPath, pos, rot, scale));
}

void Scene::Update()
{
	for (int i = 0; i < (int)m_models.size(); i++)
	{
		m_models[i].Update();
	}
}

void Scene::SetActive()
{
	m_camera.SetActive();
}
