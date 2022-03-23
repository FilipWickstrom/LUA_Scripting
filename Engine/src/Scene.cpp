#include "PCH.h"
#include "Scene.h"

Scene::Scene()
{
	//Default camera
	m_camera = Graphics::GetSceneManager()->addCameraSceneNode();
}

Scene::~Scene()
{
	Graphics::GetSceneManager()->getActiveCamera()->drop();
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
