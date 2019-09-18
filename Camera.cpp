#include "DXUT.h"
#include "Camera.h"


void Camera::CameraInit()
{
	D3DXMatrixOrthoLH(&orthographicMatrix, 1280 * 2.5f, -720 *2.5f, 0.0f, 1.0f);
	D3DXMatrixIdentity(&identityMatrix);
	following = nullptr;
}

void Camera::Update()
{
	if (following == nullptr)
		return;

	this->viewMatrix = D3DXMATRIX(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-cameraX, -cameraY, 0, 1);
}

void Camera::Follow(Node* following)
{
	this->following = following;

}

void Camera::Unfollow()
{
	this->following = nullptr;
}

bool Camera::IsFollowing() const
{
	return this->following != nullptr;
}

void Camera::SetTransform() 
{
	if (!following)
		return;

//	static int a = 1280;
	//static int b = 720;
	//D3DXMatrixOrthoLH(&orthographicMatrix, a, -b, 0.0f, 1.0f);
//	a+= 1;
//	b += 1;
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &identityMatrix);
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &viewMatrix);
}
