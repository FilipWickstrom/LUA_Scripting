#pragma once
#include <irrlicht.h>

class Camera
{
private:

	irr::scene::ICameraSceneNode* m_camera;

public:

	Camera();
	~Camera();

	void Setup();
	void SetActive();

};