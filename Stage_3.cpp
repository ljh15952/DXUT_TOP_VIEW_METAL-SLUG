#include "DXUT.h"
#include "Stage_3.h"
#include "GM.h"
#include "Bullet.h"

//12�� ���� �����ϼ�
//�÷��̾� �����ִϸ��̼�
//���� ��Ȳ���� �ִϸ��̼�
//���� ���� 3�� 360����� ����ź ��� ��������� �����;Ʒ��γ� �Ʒ��������� 
//���� ���������� �����̱�
//�浹ó��

Stage_3::Stage_3()
{
	player = new Player(L"f.png", motercycle);
	player->_position = { 100,1000 };
	player->_layer = 3;
	player->RideType = fly;
	player->_scale = { 0.5f, 0.5f};

	map = new Sprite;
	map->Create(L"stage/Stage 3/Map3.png");
	map->_position = { 0,550 };
	map->_scale = { 2.5f,2.5f };
	map->_pivot = { 0,0 };

	boss = new Boss(player);
	boss->_position = { 500,1000 };

	Camera::GetInstance()->CameraInit();
	Camera::GetInstance()->Follow(player);

	Bullet_Manager::GetInstance()->Make_Bullet();

	GM::GetInstance()->GMInit();
	GM::GetInstance()->isgamestart = true;
	GM::GetInstance()->stagenum = 3;
}

void Stage_3::Collide()
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

void Stage_3::Update()
{
	Camera::GetInstance()->SetPos({ player->_position.x + 800 , player->_position.y });
	Camera::GetInstance()->Update();
	Camera::GetInstance()->SetTransform();

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

void Stage_3::Clear()
{
	cout << "STAGE_3 END " << endl;
}
