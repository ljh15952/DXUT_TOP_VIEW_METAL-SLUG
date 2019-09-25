#include "DXUT.h"
#include "minigame.h"
#include "MainScene.h"
minigame::minigame()
{
	player = new Player(L"m/MotorCycle 1.png", motercycle);
	player->_position = { 500,500 };

	for (int i = 0; i < 10; i++)
	{
		Shotenemy[i] = new ShotEnemy(player);
		Shotenemy[i]->_scale = { 2,2 };
		Shotenemy[i]->_rotation = 1.5f;
		Shotenemy[i]->_position = { 0 + float(100 * i),-50 };
		e.push_back(Shotenemy[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		Shotenemy[i] = new ShotEnemy(player);
		Shotenemy[i]->_scale = { 2,2 };
		Shotenemy[i]->_rotation = 1.5f;
		Shotenemy[i]->_position = { -50,0 + float(100 * i) };
		e.push_back(Shotenemy[i]);

	}
	for (int i = 0; i < 10; i++)
	{
		Shotenemy[i] = new ShotEnemy(player);
		Shotenemy[i]->_scale = { 2,2 };
		Shotenemy[i]->_rotation = 1.5f;
		Shotenemy[i]->_position = { 950,0 + float(100 * i) };
		e.push_back(Shotenemy[i]);

	}
	for (int i = 0; i < 10; i++)
	{
		Shotenemy[i] = new ShotEnemy(player);
		Shotenemy[i]->_scale = { 2,2 };
		Shotenemy[i]->_rotation = 1.5f;
		Shotenemy[i]->_position = { 0 + float(100 * i),950 };
		e.push_back(Shotenemy[i]);

	}
	timer = 1;
	scorenum = 0;

	Scorelabel = new Label;
	Scorelabel->_position = { 640,700 };
	Scorelabel->Create_Label(scorenum);

	Camera::GetInstance()->CameraInit();
	Camera::GetInstance()->Follow(player);

	Bullet_Manager::GetInstance()->Make_Bullet();

	GM::GetInstance()->GMInit();
	GM::GetInstance()->stagenum = 1;
}

void minigame::Clear()
{
	Scorelabel->Delete_Label();
	delete Scorelabel;
	for (auto it : e)
	{
		delete it;
	}
	e.clear();
	GM::GetInstance()->deleteLabel();
	Bullet_Manager::GetInstance()->Delete_Bullet();
	delete player;
}

void minigame::Collide()
{
	for (auto it : Bullet_Manager::GetInstance()->_bullets)
	{
		if (it->_visible && !it->isHit)
		{
			if (!player->isJump)
				it->CollideBullet(player);
		}
	}
}

void minigame::Update()
{
	Camera::GetInstance()->SetPos({ player->_position.x  , player->_position.y });
	Camera::GetInstance()->Update();
	Camera::GetInstance()->SetTransform();

	if (player->ishit)
	{
		GM::GetInstance()->isgamestart = false;
		if (DXUTWasKeyPressed(VK_SPACE))
		{
			Director::GetInstance()->ChangeScene(new MainScene);
			return;
		}
	}

	if (DXUTWasKeyPressed(VK_SPACE))
		GM::GetInstance()->isgamestart = true;

	if (GM::GetInstance()->isgamestart)
	{
		timer -= Time::deltaTime;
		if (timer < 0)
		{
			scorenum++;
			Scorelabel->Create_Label(scorenum);
			timer = 1;
		}
	}
}
