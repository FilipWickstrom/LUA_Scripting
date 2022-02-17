#include "Object.h"

Object::Object()
{

}

Object::~Object()
{

}

Object::Object(irr::core::vector3df& pos, irr::core::vector3df& rot, irr::core::vector3df& scale)
{
	m_position = pos;
	m_rotation = rot;
	m_scale = scale;
}

void Object::SetPosition(irr::core::vector3df pos)
{
	m_position = pos;
}

void Object::SetRotation(irr::core::vector3df rot)
{
	m_rotation = rot;
}

void Object::SetScale(irr::core::vector3df scale)
{
	m_scale = scale;
}
