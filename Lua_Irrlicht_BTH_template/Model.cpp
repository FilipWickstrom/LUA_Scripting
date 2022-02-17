#include "Model.h"
#include "Graphics.h"
#include <iostream>

void Model::LoadMesh(std::string& meshName)
{
	meshName = "../Bin/Meshes/" + meshName;

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

void Model::Update()
{
	m_node->setPosition(m_position);
	m_node->setRotation(m_rotation);
	m_node->setScale(m_scale);
}
