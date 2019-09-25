#include "DXUT.h"
#include "MainScene.h"
#include "RealMainScene.h"
#include "minigame.h"

//spawntimer = 1;
//적 스포너
	/*spawntimer -= Time::deltaTime;
	if (spawntimer < 0)
	{
		vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
		switch (rand() % 3)
		{
		case 0:
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::foot);
			break;
		case 1:
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::motercycle);
			break;
		case 2:
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::horse);
			break;
		}
		spawntimer = 1;
	}*/
	//

void MainScene::Init()
{
	stage = new minigame;

	//stage = new Stage_2;
//	stage = new Stage_1;
}

void MainScene::Update()
{
	stage->Update();
	stage->Collide();

	
	if (DXUTWasKeyPressed('Q'))
	{
		delete stage;
		stage = new Stage_2;
	}
	if (DXUTWasKeyPressed('W'))
	{
		delete stage;
		stage = new Stage_3;
	}
	/*if (DXUTWasKeyPressed('X'))
		Director::GetInstance()->ChangeScene(new MainScene);*/
}

void MainScene::OnExit()
{
	stage->Clear();
	delete stage;
}

