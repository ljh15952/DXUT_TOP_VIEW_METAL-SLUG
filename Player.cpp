#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	Create(L"a/Handgun_Walk 1.png");


	ShotPos = new Sprite;
	ShotPos->Create(L"UFO_1.png");
	ShotPos->_scale = { 0.1f,0.1f };
	ShotPos->_position = { 100,100 };

	RideType = Ride_type::foot;
	Hp = 3;
	Speed = 10;
	isJump = false;
	jumpTimer = 0.5f;

	shot_type = P_shot_type::pistol;

	machine_gun_ammo = 30; //
	youdo_missile_ammo = 0;
	shot_timer = 0.3f;

	iscol = false;

}

void Player::Movement()
{
	iscol = false;
	if ((_position.x >= 9000 || _position.y >= 9000) || (_position.x <= 0 || _position.y <= 0))
	{
		_position -= v * (Speed + 0.1f);
		iscol = true;
	}        

 	v = { (float)Director::GetInstance()->p.x - 640 ,(float)Director::GetInstance()->p.y - 360 };
	_rotation = atan2(v.y, v.x);

	float l = sqrt(v.x * v.x + v.y * v.y);
	v.x /= l;
	v.y /= l;


	if (!isJump)
	{
		Speed = 10;
		if (DXUTIsKeyDown(VK_SPACE))
			Speed = 0;
		if (DXUTWasKeyPressed('Z'))
			isJump = true;
	}
	else 
	{
		jumpTimer -= Time::deltaTime;
		if (jumpTimer < 0)
		{
			//���� �÷��̾�� �� �̵������̶� �浹���̶��
			//�� �̵����ܿ� ���� Ÿ���ִ��� Ȯ��
			//Ÿ�������� �� �̵����� �P��Ÿ��
			//��Ÿ�������� �÷��̾� �ٷ� ��� ���ӿ���
			isJump = false;
			jumpTimer = 0.5f;
		}
		Speed = 15;

		cout << "��������~" << endl;
	}




	_position += v * Speed;

	ShotPos->_position = _position + v * 35;
}

void Player::Attack()
{
	shot_timer -= Time::deltaTime;

	if (shot_timer < 0)
	{
		switch (shot_type)
		{
		case P_shot_type::pistol:
			Bullet_Manager::GetInstance()->Shot_Bullet(ShotPos->_position, v);
			shot_timer = 0.3f;
		break;
		case P_shot_type::machine_gun:
			if (machine_gun_ammo > 0)
			{
				cout << "SHOTMACHINEGUN";
				Bullet_Manager::GetInstance()->Shot_Bullet(ShotPos->_position, v);
				machine_gun_ammo--;
				shot_timer = 0.05f;
			}
			break;
		case P_shot_type::youdo_missle:
			if (youdo_missile_ammo > 0)
			{
				cout << "SHOTYOUDO";
			}
			break;
		}
	}
}

void Player::Update()
{
	Movement();
	Animation(L"a/Handgun_Walk ", 3, 0.1f, 1);


	if (DXUTWasKeyPressed('1'))
		shot_type = P_shot_type::pistol;
	if (DXUTWasKeyPressed('2'))
		shot_type = P_shot_type::machine_gun;
	if (DXUTWasKeyPressed('3'))
		shot_type = P_shot_type::youdo_missle;

}
