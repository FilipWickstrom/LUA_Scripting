#include "Scene.h"

Scene::Scene()
{
	m_models.reserve(100);
}

Scene::~Scene()
{

}

void Scene::AddObject(std::string modelPath, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df scale)
{

}

void Scene::Update()
{
	for (int i = 0; i < (int)m_models.size(); i++)
	{
		m_models[i].Update();
	}
}
