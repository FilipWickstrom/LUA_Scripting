#include "PCH.h"
#include "Scene.h"

Scene::Scene()
{
	//Default camera
	m_camera = Graphics::GetSceneManager()->addCameraSceneNode();
}

Scene::~Scene()
{
	//Graphics::GetSceneManager()->getActiveCamera()->drop();
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

void Scene::UpdateCamera()
{
	lua_getglobal(LUA, "GetObjectPosition");
	lua_pushnumber(LUA, 0);
	int ret = lua_pcall(LUA, 1, 2, 0);

	if (ret == 0)
	{
		if (lua_isnumber(LUA, -1) && lua_isnumber(LUA, -2))
		{
			irr::f32 x = static_cast<irr::f32>(lua_tonumber(LUA, -2));
			irr::f32 z = static_cast<irr::f32>(lua_tonumber(LUA, -1));

			if (m_camera)
			{
				// + 1 to look in the correct direction, z positive
				m_camera->setTarget({ x, 0, z + 1 });
				m_camera->setPosition({ x, 40.f, z });
			}
		}
		else
		{
			// 'Err' was returned, do something like delete this object or something idk.
		}
		lua_pop(LUA, 2);
	}
	else
	{
		std::cout << lua_tostring(LUA, -1) << "\n";
		lua_pop(LUA, 1);
	}
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
