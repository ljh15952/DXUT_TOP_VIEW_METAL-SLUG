#include "DXUT.h"
#include "Stage_1.h"

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


	P = new Player;
	P->_position = { 1600,2300 };
	this->AddChild(P, 1);

	S2 = new Sprite;
	S2->Create(L"asd.png");
	S2->_pivot = { 0,0 };
	this->AddChild(S2, 0);


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
		w->Create(L"w.png");
		w->_visible = false;
		walls.push_back(w);
	}
	walls[0]->_position = { 1150,1000 };
	walls[1]->_position = { 6150,1000 };
	walls[2]->_position = { 8650,1000 };
	walls[3]->_position = { 3650,3600 };
	walls[4]->_position = { 6200,3600 };
	walls[5]->_position = { 8550,3600 };
	walls[6]->_position = { 1250,6150 };
	walls[7]->_position = { 3670,6150 };
	walls[8]->_position = { 8650,6150 };
	walls[9]->_position = { 1250,8750 };
	walls[10]->_position = { 3670,8750 };
	walls[11]->_position = { 6200,8750 };
	walls[12]->_position = { 8670,8730 };
	//


	TrasgManager::GetInstance()->Make_Trash();

	Bullet_Manager::GetInstance()->Make_Bullet();

	Minimap = new MiniMap(P);

	Camera::GetInstance()->CameraInit();
	Camera::GetInstance()->Follow(P);


	UI::GetInstance()->UI_Init();
	GM::GetInstance()->GMInit();


	AddRenderTarget();
}

Stage_1::~Stage_1()
{
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

	if (Director::GetInstance()->OnMouseDown())
	{
		P->isshot = true;
		P->shot_timer = 0;

		if (UI::GetInstance()->isScript)
		{
			UI::GetInstance()->SetNextScriptUI();
		}
	}
	else if (Director::GetInstance()->OnMouse())
	{
		P->Attack();
	}
	else if (Director::GetInstance()->OnMouseUp())
	{
		P->isshot = false;
	}
}

void Stage_1::Update()
{
	//카메라 업데이트 공통
	Camera::GetInstance()->SetPos({ P->_position.x , P->_position.y });
	Camera::GetInstance()->Update();
	Camera::GetInstance()->SetTransform();
	//

	GM::GetInstance()->UpdateTimer();

	feulSp->_scale.x = P->feul / 10;

}
