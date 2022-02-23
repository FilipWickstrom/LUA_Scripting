#include "Model.h"
#include "Graphics.h"
#include <iostream>
#include "LuaHandler.h"

void Model::LoadMesh(std::string& meshName)
{
	meshName = "../../Bin/Meshes/" + meshName;

	irr::scene::IMesh* mesh = Graphics::GetSceneManager()->getMesh(meshName.c_str());
	if (mesh == nullptr)
		std::cout << "Failed to get: " << meshName << std::endl;

	m_node = Graphics::GetSceneManager()->addMeshSceneNode(mesh);
}

Model::Model(std::string& meshName)
	:Object()
{
	this->LoadMesh(meshName);
}

Model::Model(std::string& meshName, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df scale)
	:Object(pos, rot, scale)
{
	this->LoadMesh(meshName);
}

Model::Model(std::string& meshName, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df scale, unsigned int& id)
	:Object(pos, rot, scale)
{
	this->LoadMesh(meshName);
	m_id = id;
}

void Model::SetID(unsigned int id)
{
	m_id = id;
}

const unsigned int& Model::GetID() const
{
	return m_id;
}

void Model::Update()
{
	// Gather the position from LUA
	lua_getglobal(LUA, "getMonsterPosition");
	lua_pushnumber(LUA, 1);
	int ret = lua_pcall(LUA, 1, 2, 0);

	if (ret == 0)
	{
		m_position.X = lua_tonumber(LUA, -2);
		m_position.Z = lua_tonumber(LUA, -1);
		lua_pop(LUA, 2);
	}
	else
	{
		lua_pop(LUA, 1);
	}

	if (m_node)
	{
		m_node->setPosition(m_position);
		m_node->setRotation(m_rotation);
		m_node->setScale(m_scale);
	}
}
