#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	S1 = new Sprite;
	S1->Create(L"soldier1_gun.png");
	S1->_position = { 100,100 };
	this->AddChild(S1, 3);

	S2 = new Sprite;
	S2->Create(L"UFO_1.png");
	S2->_position = { 300,300 };
	this->AddChild(S2, 2);

	Camera::GetInstance()->CameraInit();
	Camera::GetInstance()->Follow(S1);
}

void MainScene::Update()
{
	Camera::GetInstance()->SetPos({ S1->_position.x, S1->_position.y });

	Camera::GetInstance()->Update();

	Camera::GetInstance()->SetTransform();



	vector2 v = { (float)Director::GetInstance()->p.x - 640 ,(float)Director::GetInstance()->p.y - 360 };
	S1->_rotation = atan2(v.y, v.x);

	float l = sqrt(v.x * v.x + v.y * v.y);
	v.x /= l;
	v.y /= l;
	S1->_position += v * 5;


	RECT TEMP;
	if (IntersectRect(&TEMP, &S1->GetRect(), &S2->GetRect()))
	{
		S1->_position -= v * 5.1f;
	}
}

void MainScene::OnExit()
{
}

