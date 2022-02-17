#pragma once
#include <irrlicht.h>

class Object
{
protected:

	irr::core::vector3df m_position;
	irr::core::vector3df m_rotation;
	irr::core::vector3df m_scale;

public:

	Object();
	~Object();
	Object(irr::core::vector3df& pos, irr::core::vector3df& rot,
		irr::core::vector3df& scale);

	void SetPosition(irr::core::vector3df pos);
	void SetRotation(irr::core::vector3df rot);
	void SetScale(irr::core::vector3df scale);

};