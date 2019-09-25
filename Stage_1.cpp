#include "DXUT.h"
#include "Stage_1.h"
#include "MainScene.h"

//GM하고 UI어떠케좀 해봐ㅡㅡ;
//스크립트어케짜지
//isscript일때 게임을 잠깐 멈추고
//스크립트가뜸 스크립트들은 전부 vector안에 들어있는 형식
//클릭한번에
//Sprite * nowscript;
//nowscript = script[++num]; 이런식으로
//nowspeak = speak[++num]; 이런식으로
Stage_1::Stage_1()
{
	for (int i = 0; i < 10; i++)
	{
		Sprite* k = new Sprite;
		k->Create(L"k/Kickboard 1.png");
		k->_position = { 1600 + float(100 * i),2300 };
		k->_layer = 1;
		k->_scale = { 1.7f,1.7f };
		kick.push_back(k);
	}
	kick[0]->_position = { 1750,2500 };
	kick[1]->_position = { 4250,1750 };
	kick[2]->_position = { 6558.84,2444.84 };
	kick[3]->_position = { 7472.63,4033.44 };
	kick[4]->_position = { 6779.15,5660.47 };
	kick[5]->_position = { 6788.54,6679.89 };
	kick[6]->_position = { 7971.3,7615.05 };
	kick[7]->_position = { 5411.36,7601.43 };
	kick[8]->_position = { 4805.59,8605.6 };
	kick[9]->_position = { 1010.59,7569.32 };


	P = new Player(L"a/Walk/AR_walk 1.png",foot);
	P->_position = { 2000,1800 };
	P->_layer = 1;

	S2 = new Sprite;
	S2->Create(L"stage_1/map.png");
	S2->_pivot = { 0,0 };


	feulSp = new Sprite;
	feulSp->Create(L"fuel.png");
	feulSp->_position = { 590,400 };
	feulSp->_pivot = { 0,0 };
	feulSp->isUI = true;


	EnemyManager::GetInstance()->Make_Enemy();
	for (int i = 0; i < 2; i++)
	{
		EnemyManager::GetInstance()->SetEnemy({ 2000,2200 + float(200 * i) }, Ride_type::foot);
	}

	//set wall            
	for (int i = 0; i < 13; i++)
	{
		Sprite* w = new Sprite;
		w->Create(L"w2.png");
		w->_visible = false;
		walls.push_back(w);
	}
	walls[0]->_position = { 402.116 + 675,347.52 + 675 };
	walls[1]->_position = { 2198.77 + 675,347.52 + 675 };
	walls[2]->_position = { 4002.22 + 675,347.52 + 675 };
	walls[3]->_position = { 5782.11 + 675,347.52 + 675 };

	walls[4]->_position = { 402.116 + 675,2059.2 + 675 };
	walls[5]->_position = { 2198.77 + 675,2059.2 + 675 };
	walls[6]->_position = { 4002.22 + 675,2059.2 + 675 };
	walls[7]->_position = { 5782.11 + 675,2059.2 + 675 };

	walls[8]->_position = { 5782.11 + 675,3759 + 675 };
	walls[9]->_position = { 402.116 + 675,5470.13 + 675 };
	walls[10]->_position = { 2198.77 + 675,5470.13 + 675 };
	walls[12]->_position = { 4002.22 + 675,5470.13 + 675 };
	walls[11]->_position = { 5782.11 + 675,5470.13 + 675 };
	////


	TrasgManager::GetInstance()->Make_Trash();

	Bullet_Manager::GetInstance()->Make_Bullet();

	Minimap = new MiniMap(P);

	Camera::GetInstance()->CameraInit();
	Camera::GetInstance()->Follow(P);


	UI::GetInstance()->UI_Init();
	GM::GetInstance()->GMInit();
	GM::GetInstance()->stagenum = 1;
	GM::GetInstance()->isgamestart = true;
}

void Stage_1::Clear()
{
	cout << "123" << endl;
	delete P;
	delete S2;
	delete Minimap;
	delete feulSp;
	EnemyManager::GetInstance()->Delete_Enemys();
	TrasgManager::GetInstance()->Delete_Trash();
	Bullet_Manager::GetInstance()->Delete_Bullet();
	UI::GetInstance()->DeleteUI();
	GM::GetInstance()->deleteLabel();
	for (auto it : kick)
	{
		delete it;
	}
	kick.clear();

	for (auto it : walls)
	{
		delete it;
	}
	walls.clear();
}

void Stage_1::Collide()
{
	//스쿠터타기
	for (auto it : kick)
	{
		RECT TEMP;
		if (IntersectRect(&TEMP, &P->GetRect(), &it->GetRect()))
		{
			it->_position = { -5000,-5000 };
			P->Set_P_KickBoard_State();
			if (P->RideType != Ride_type::foot)
				P->feul = 10;
		}
	}
	//

	//벽 충돌처리
	for (auto it : walls)
	{
		RECT TEMP;
		if (IntersectRect(&TEMP, &P->GetRect(), &it->GetRect()))
		{
			P->_position -= P->v * P->Speed;
			P->iscol = true;
		}
	}
	//

	//쓰래기 충돌처리
	P->isoil = false;
	for (auto it : TrasgManager::GetInstance()->Trashs)
	{
		RECT TEMP;
		if (IntersectRect(&TEMP, &P->GetRect(), &it->GetRect()))
		{
			if (it->t == T_Trash_Type::oil)
			{
				P->isoil = true;
			}
			else if (it->t == T_Trash_Type::trash)
			{
				if (it->_visible)
				{
					P->isHit();
					it->_visible = false;
				}
			}
		}
	}
	//플레이어 점프 충돌처리
	if (P->isJump)
	{
		for (auto it : EnemyManager::GetInstance()->_enemys)
		{
			if (it->_visible && it->isDie)
			{
				RECT TEMP;
				if (IntersectRect(&TEMP, &P->GetRect(), &it->GetRect()))
				{
					switch (it->RideType)
					{
					case horse:
						P->Set_P_Horse_State();
						break;
					case motercycle:
						P->Set_P_MotorCycle_State();
						break;
					}
					P->AddFeul();
				}
			}
		}
	}
	//

	for (auto it : Bullet_Manager::GetInstance()->_bullets)
	{
		for (auto it2 : EnemyManager::GetInstance()->_enemys)
		{
			if (it->_visible && !it->isHit)
			{
				it->CollideBullet(P);

				if (it2->_visible && !it2->isDie)
				{
					it->CollideBullet(it2);
				}
			}
		}
		for (auto it3 : TrasgManager::GetInstance()->Trashs)
		{
			if (it->_mytype == T_My_Type::player && it3->t == T_Trash_Type::trash && it3->_visible && !it->isHit)
			{
				RECT TEMP;
				if (IntersectRect(&TEMP, &it->GetRect(), &it3->GetRect()))
				{
					it3->_visible = false;
					it->isHit = true;
				}
			}
		}

	}

	
}

void Stage_1::Update()
{
	//카메라 업데이트 공통
	Camera::GetInstance()->SetPos({ P->_position.x , P->_position.y });
	Camera::GetInstance()->Update();
	Camera::GetInstance()->SetTransform();
	//
	if(DXUTWasKeyPressed('F'))
		cout << P->_position.x << " " << P->_position.y << endl;

	GM::GetInstance()->UpdateTimer();

	feulSp->_scale.x = P->feul / 10;

	if (Director::GetInstance()->OnMouseDown())
	{
		P->isshot = true;
		P->shot_timer = 0;

		//if (UI::GetInstance()->isScript)
		//{
		//	UI::GetInstance()->SetNextScriptUI();
		//}
	}
	else if (Director::GetInstance()->OnMouse())
	{                                                              
		P->Attack();
	}
	else if (Director::GetInstance()->OnMouseUp())
	{
		P->isshot = false;
	}

	if (DXUTWasKeyPressed('E'))
		Director::GetInstance()->ChangeScene(new MainScene);
}
