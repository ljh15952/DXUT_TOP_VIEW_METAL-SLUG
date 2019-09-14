#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	S1 = new Sprite;
	S1->Create(L"soldier1_gun.png");
	S1->_position = { 100,100 };
	this->AddChild(S1, 3);

	_S1 = new Sprite;
	_S1->Create(L"UFO_1.png");
	_S1->_scale = { 0.1f,0.1f };
	_S1->_position = { 100,100 };
	this->AddChild(_S1, 3);

	S2 = new Sprite;
	S2->Create(L"UFO_1.png");
	S2->_position = { 300,300 };
	this->AddChild(S2, 2);

	Bullet_Manager::GetInstance()->Make_Bullet();

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
	if (!DXUTIsKeyDown(VK_SPACE))
		S1->_position += v * 5;

	_S1->_position = S1->_position + v * 35;

	RECT TEMP;
	if (IntersectRect(&TEMP, &S1->GetRect(), &S2->GetRect()))
	{
		S1->_position -= v * 5.1f;
	}

	if (Director::GetInstance()->OnMouseDown())
	{

	}
	else if (Director::GetInstance()->OnMouse())
	{
		cout << "SHOOT" << endl;
		Bullet_Manager::GetInstance()->Shot_Bullet(_S1->_position, v);
	}

}

void MainScene::OnExit()
{
}

