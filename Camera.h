#pragma once
#include "Sprite.h"
#include "Types.h"
class Camera : public Singleton<Camera>
{
public:
	void CameraInit();
	void Update();
	void Follow(Node* following);
	void Unfollow();
	bool IsFollowing() const;
	void SetTransform() const;

	void SetPos(vector2 v) { cameraX = v.x, cameraY = v.y; };

	int cameraX;
	int cameraY;

private:
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;

	Node* following;


};

