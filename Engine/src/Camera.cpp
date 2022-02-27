#include "PCH.h"
#include "Camera.h"


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

void Camera::SetActive()
{
	Graphics::GetSceneManager()->setActiveCamera(m_camera);
}
