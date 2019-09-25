#include "DXUT.h"
#include "Stage_2.h"
#include "Bullet.h"
#include "UI.h"
Stage_2::Stage_2()
{
	cout << "STAGE_2 START " << endl;

	map = new Sprite;
	map->Create(L"stage/Stage 2/1P.G.png");
	map->_position = { 0,0 };
	map->_pivot = { 0,0 };
	map->_scale = { 2.5f,2.5f };

	player = new Player(L"m/MotorCycle 1.png", motercycle);
	player->_position = { 100,1000 };

	//s = new Stage_1_Script;
	
	for (int i = 0; i < 50; i++)
	{
		Shotenemy[i] = new ShotEnemy(player);
		Shotenemy[i]->_scale = { 2,2 };
		Shotenemy[i]->_rotation = 1.5f;
		Shotenemy[i]->_position = { 100 + float(500 * i),450 };
	}
	for (int i = 50; i < 100; i++)
	{
		Shotenemy[i] = new ShotEnemy(player);
		Shotenemy[i]->_scale = { 2,2 };
		Shotenemy[i]->_rotation = -1.5f;
		Shotenemy[i]->_position = { 100 + float(500 * (i-50)),1350 };
	}


	Camera::GetInstance()->CameraInit();
	Camera::GetInstance()->Follow(player);

	GM::GetInstance()->GMInit();
	GM::GetInstance()->stagenum = 2;
	GM::GetInstance()->isgamestart = true;

	UI::GetInstance()->UI_Init();

	Bullet_Manager::GetInstance()->Make_Bullet();

}

void Stage_2::Clear()
{
	cout << "STAGE_2 END " << endl;
}


void Stage_2::Collide()
{
	for (auto it : Bullet_Manager::GetInstance()->_bullets)
	{
		if (it->_visible && !it->isHit)
		{
			if(!player->isJump)
				it->CollideBullet(player);

			for (int i = 0; i < 100; i++)
			{
				RECT r;
				if (IntersectRect(&r, &Shotenemy[i]->GetRect(), &it->GetRect()))
				{
					it->CollideBullet(Shotenemy[i]);
				}
			}
		}
	}

}

void Stage_2::Update()
{
	Camera::GetInstance()->SetPos({ player->_position.x + 800 , player->_position.y });
	Camera::GetInstance()->Update();
	Camera::GetInstance()->SetTransform();

	//if (DXUTWasKeyPressed('X'))
		//s->SetNextScript();

	if (Director::GetInstance()->OnMouseDown())
	{
		player->isshot = true;
		player->shot_timer = 0;
	}
	else if (Director::GetInstance()->OnMouse())
	{
		player->Attack();
	}
	else if (Director::GetInstance()->OnMouseUp())
	{
		player->isshot = false;
	}
}

