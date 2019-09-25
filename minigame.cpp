#include "DXUT.h"
#include "minigame.h"
#include "MainScene.h"
minigame::minigame()
{
	player = new Player(L"m/MotorCycle 1.png", motercycle);
	player->_position = { 500,500 };
	player->_scale = { 0.5f,0.5f };
	for (int i = 0; i < 10; i++)
	{
		Shotenemy[i] = new ShotEnemy(player);
		Shotenemy[i]->_scale = { 2,2 };
		Shotenemy[i]->_rotation = 1.5f;
		Shotenemy[i]->_position = { 100 + float(100 * i),50 };
		e.push_back(Shotenemy[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		Shotenemy[i] = new ShotEnemy(player);
		Shotenemy[i]->_scale = { 2,2 };
		Shotenemy[i]->_rotation = 1.5f;
		Shotenemy[i]->_position = { 50,100 + float(100 * i) };
		e.push_back(Shotenemy[i]);

	}
	for (int i = 0; i < 10; i++)
	{
		Shotenemy[i] = new ShotEnemy(player);
		Shotenemy[i]->_scale = { 2,2 };
		Shotenemy[i]->_rotation = 1.5f;
		Shotenemy[i]->_position = { 1050,100 + float(100 * i) };
		e.push_back(Shotenemy[i]);

	}
	for (int i = 0; i < 10; i++)
	{
		Shotenemy[i] = new ShotEnemy(player);
		Shotenemy[i]->_scale = { 2,2 };
		Shotenemy[i]->_rotation = 1.5f;
		Shotenemy[i]->_position = { 100 + float(100 * i),1050 };
		e.push_back(Shotenemy[i]);

	}

	m = new Sprite;
	m->Create(L"SpeedUp.png");
	m->_scale = { 0.3f,0.3f };
	m->isUI = true;

	enerygy = new Sprite;
	enerygy->Create(L"fuel2.png");
	enerygy->_position = { 630,370 };
	enerygy->_pivot = { 0,0 };
	enerygy->isUI = true;

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

	istracer = false;
}

void minigame::Clear()
{
	Scorelabel->Delete_Label();
	delete Scorelabel;
	delete m;
	for (auto it : e)
	{
		delete it;
	}
	e.clear();
	delete enerygy;
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

	m->_position = Director::GetInstance()->GetMousePos();


	if (player->ishit)
	{
		GM::GetInstance()->isgamestart = false;
		if (DXUTWasKeyPressed(VK_SPACE))
		{
			Director::GetInstance()->ChangeScene(new MainScene);
			return;
		}
	}

	if (enerygy->_scale.x <= 1 && !istracer)
	{
		enerygy->_scale.x += Time::deltaTime;
		if (enerygy->_scale.x >= 1)
			enerygy->_scale.x = 1;
	}

	if (Director::GetInstance()->OnMouseDown())
	{
		istracer = true;
	}
	else if (Director::GetInstance()->OnMouse())
	{
		if (enerygy->_scale.x >= 0)
		{
			enerygy->_scale.x -= Time::deltaTime;
		}
		else
		{
			istracer = false;
		}
	}
	else if (Director::GetInstance()->OnMouseUp())
	{
		istracer = false;
	}
	if (istracer)
	{
		Time::timeScale = 0.1f;
	}
	else
	{
		Time::timeScale = 1;
	}

	cout << enerygy->_scale.x << endl;


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
