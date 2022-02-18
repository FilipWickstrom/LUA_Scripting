#include "Camera.h"
#include "Graphics.h"

Camera::Camera()
{
	m_camera = nullptr;
}

Camera::~Camera()
{
}

void Camera::Setup()
{
	m_camera = Graphics::GetSceneManager()->addCameraSceneNode(0, { 0,20,0 }, { 0,0,0 });

	irr::core::matrix4 orthoMatrix;
	orthoMatrix.buildProjectionMatrixOrthoLH(50, 26, 0, 20);
	m_camera->setProjectionMatrix(orthoMatrix);
}
