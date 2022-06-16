#include "PCH.h"
#include "Model.h"

unsigned int Model::s_idCounter = 0;

void Model::LoadMesh(const std::string& meshName)
{
	irr::video::ITexture* texture = Graphics::GetDriver()->getTexture((SPRITEPATH + meshName).c_str());
	irr::core::dimension2df size = { 16.f, 16.f };
	if (texture)
		size = static_cast<irr::core::dimension2df>(texture->getSize());

	irr::scene::IMesh* mesh = Graphics::GetGeometryCreator()->createPlaneMesh({ size / SPRITE_SIZE_MODIFIER });

	m_node = Graphics::GetSceneManager()->addMeshSceneNode(mesh, 0, s_idCounter);

	if (!m_node)
		std::cout << "ERROR: Node not correct..." << std::endl;

	if (texture)
		m_node->setMaterialTexture(0, texture);

	//Make it possible to see using directX or openGL
	m_node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
	//Possible to rotate the sprite
	m_node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_BACK_FACE_CULLING, false);
	//Turn off filtering - no interpolation between pixels
	m_node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_BILINEAR_FILTER, false);
	//Alpha value makes it transparent
	m_node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
}

Model::Model()
{
	m_id = s_idCounter++;
	m_node = nullptr;
	this->LoadMesh("default.png");
}

Model::Model(const std::string& meshName)
{
	m_id = s_idCounter++;
	m_node = nullptr;
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
	if (m_node)
		m_node->setPosition(pos);
}

void Model::SetScale(const float& scale)
{
	if (m_node)
		m_node->setScale({ scale, scale, scale });
}

void Model::Update()
{
	// Gather the position from LUA
	lua_getglobal(LUA, "GetObjectPosition");
	lua_pushnumber(LUA, m_id);
	
	if (!LuaHandler::CheckErrors(1, 2))
	{
		if (lua_isnumber(LUA, -1))
		{
			irr::core::vector3df vec;
			vec.X = static_cast<irr::f32>(lua_tonumber(LUA, -1));
			vec.Y = 0.f;
			vec.Z = static_cast<irr::f32>(lua_tonumber(LUA, -2));

			if (m_node)
				m_node->setPosition(vec);
		}
		else
		{
			// 'Err' was returned, do something like delete this object or something idk.
		}
		lua_pop(LUA, 2);
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
