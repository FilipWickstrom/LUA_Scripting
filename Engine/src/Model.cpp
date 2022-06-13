#include "PCH.h"
#include "Model.h"

unsigned int Model::s_idCounter = 0;

void Model::LoadMesh(std::string& meshName)
{
	meshName = MODELPATH + meshName;

	irr::scene::IMesh* mesh = Graphics::GetSceneManager()->getMesh(meshName.c_str());
	if (mesh == nullptr)
		std::cout << "Failed to get: " << meshName << std::endl;

	m_node = Graphics::GetSceneManager()->addMeshSceneNode(mesh);
	m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

Model::Model(std::string& meshName)
	:Object()
{
	m_id = s_idCounter++;
	this->LoadMesh(meshName);
}

Model::Model(std::string& meshName, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df scale)
	:Object(pos, rot, scale)
{
	m_id = s_idCounter++;
	this->LoadMesh(meshName);
}

void Model::SetID(unsigned int id)
{
	m_id = id;
}

unsigned int Model::GetID() const
{
	return m_id;
}

void Model::SetPosition(const irr::core::vector3df& pos)
{
	m_position = pos;
	if (m_node)
	{
		m_node->setPosition(m_position);
	}
}

void Model::SetScale(const float& scale)
{
	m_scale = { scale, scale, scale };
	m_node->setScale(m_scale);
}

void Model::Update()
{
	// Gather the position from LUA
	lua_getglobal(LUA, "GetObjectPosition");
	lua_pushnumber(LUA, m_id);
	int ret = lua_pcall(LUA, 1, 2, 0);

	if (ret == 0)
	{
		if (lua_isnumber(LUA, -1))
		{
			m_position.X = static_cast<irr::f32>(lua_tonumber(LUA, -1));
			m_position.Y = 0.f;
			m_position.Z = static_cast<irr::f32>(lua_tonumber(LUA, -2));

			if (m_node)
			{
				m_node->setPosition(m_position);
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

void Model::Drop()
{
	if (m_node)
	{
		m_node->remove();
		m_node = nullptr;
	}
}
