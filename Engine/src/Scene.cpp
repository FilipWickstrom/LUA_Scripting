#include "PCH.h"
#include "Scene.h"

Scene::Scene()
{
	m_defaultCamera = Graphics::GetSceneManager()->addCameraSceneNode();
}

Scene::~Scene()
{
	RemoveCamera();
}

unsigned int Scene::AddModel(std::string& file)
{
	Model model(file, { 0.f, 0.f, 0.f }, { 0.f,0.f,0.f }, { 1.f, 1.f, 1.f });
	unsigned int id = model.GetID();
	m_models[id] = model;
	return id;
}

void Scene::RemoveModel(unsigned int id)
{
	m_models.at(id).Drop();
	m_models.erase(id);
}

void Scene::UpdatePosition(unsigned int id, const irr::core::vector3df& pos)
{
	if(m_models.find(id) != m_models.end())
		m_models.at(id).SetPosition(pos);
}

bool Scene::RemoveCamera()
{
	bool removed = false;
	irr::scene::ICameraSceneNode* oldCam = Graphics::GetSceneManager()->getActiveCamera();
	if (oldCam)
	{
		Graphics::GetSceneManager()->setActiveCamera(0);
		oldCam->remove();
		removed = true;
	}
	return removed;
}
