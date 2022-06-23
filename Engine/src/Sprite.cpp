#include "PCH.h"
#include "Sprite.h"

Sprite::Sprite()
{
	m_node = nullptr;
	this->LoadTexture("default.png");
}

Sprite::Sprite(const std::string& textureName)
{
	m_node = nullptr;
	this->LoadTexture(textureName);
}

void Sprite::SetPosition(const irr::core::vector3df& pos)
{
	m_node->setPosition(pos);
}

void Sprite::SetRotation(const irr::core::vector3df& rot)
{
	m_node->setRotation(rot);
}

void Sprite::SetScale(const irr::core::vector3df& scl)
{
	m_node->setScale(scl);
}

void Sprite::LoadTexture(const std::string& filename)
{
	// Cleaning up before loading new
	this->Remove();

	irr::video::ITexture* texture = Graphics::GetDriver()->getTexture((SPRITEPATH + filename).c_str());
	irr::core::dimension2df size = { 16.f, 16.f };
	if (texture)
		size = static_cast<irr::core::dimension2df>(texture->getSize());
	
	irr::scene::IMesh* mesh = Graphics::GetGeometryCreator()->createPlaneMesh({ size / SPRITE_SIZE_MODIFIER });
	
	m_node = Graphics::GetSceneManager()->addMeshSceneNode(mesh);

	if (!m_node)
		std::cout << "ERROR: Node not correct..." << std::endl;

	if (texture)
		m_node->setMaterialTexture(0, texture);

	//Make it possible to see using directX or openGL
	m_node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
	//Possible to rotate the sprite
	m_node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_BACK_FACE_CULLING, false);
	//Alpha value makes it transparent
	m_node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	//Turn off filtering - no interpolation
	m_node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_BILINEAR_FILTER, false);
}

void Sprite::Remove()
{
	if (m_node)
		m_node->remove();
}

void Sprite::SetVisible(const bool& isVisible)
{
	if (m_node)
		m_node->setVisible(isVisible);
}

