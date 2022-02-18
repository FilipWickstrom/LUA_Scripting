#include "Scene.h"

Scene::Scene()
{
	m_camera.Setup();
}

Scene::~Scene()
{

}

void Scene::AddObject(std::string modelPath, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df scale)
{
	m_models.push_back(Model(modelPath, pos, rot, scale));
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
