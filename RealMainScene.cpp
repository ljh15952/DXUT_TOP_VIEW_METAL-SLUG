#include "DXUT.h"
#include "RealMainScene.h"
#include "MainScene.h"
void RealMainScene::Init()
{
	load = new Sprite;
	load->Create(L"LOAD.png");
	load->_position = { 640,360 };
	load->isUI = true;


	bg = new Sprite;
	bg->Create(L"Main/Main.png");
	bg->_position = { 640,360 };
	bg->isUI = true;

	timer = 0.1f;
	isclick = false;
}

void RealMainScene::Update()
{
	if (Director::GetInstance()->OnMouseDown())
	{
		isclick = true;
		if (PtInRect(&bg->GetRect(), Director::GetInstance()->p))
		{
			bg->_visible = false;
		}
	}
	if (isclick)
	{
		timer -= Time::deltaTime;
		if (timer < 0)
		{
			Director::GetInstance()->ChangeScene(new MainScene);
		}
	}
}

void RealMainScene::OnExit()
{
	delete bg;
	delete load;
}
