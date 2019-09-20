#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	Create(L"a/Walk/AR_walk 1.png");
	_scale = { 1.7f,1.7f };

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
	_mytype = T_My_Type::player;

	machine_gun_ammo = 500; //
	youdo_missile_ammo = 0;
	shot_timer = 0.3f;

	iscol = false;
	isshot = false;

	feul = 0;

	Anistate = T_Player_AniState::pistol_walk;

}

void Player::Movement()
{
	iscol = false;
	if ((_position.x >= 9850 || _position.y >= 9850) || (_position.x <= 0 || _position.y <= 0))
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
			//만약 플레이어랑 적 이동수단이랑 충돌중이라면
			//적 이동수단에 적이 타고있는지 확인
			//타고있으면 적 이동수단 뻇어타고
			//안타고있으면 플레이어 바로 사망 게임오버
			isJump = false;
			jumpTimer = 0.5f;
		}
		Speed = 15;

		cout << "점프중임~" << endl;
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
			Bullet_Manager::GetInstance()->Shot_Bullet(ShotPos->_position, v,_mytype);
			shot_timer = 0.3f;
			Anistate = T_Player_AniState::pistol_shot;
			break;
		case P_shot_type::machine_gun:
			Anistate = T_Player_AniState::machinegun_shot;
			if (machine_gun_ammo > 0)
			{
				Bullet_Manager::GetInstance()->Shot_Bullet(ShotPos->_position, { v.x,v.y }, _mytype);
				machine_gun_ammo--;
				shot_timer = 0.05f;
			}
			break;
		case P_shot_type::youdo_missle:
			if (youdo_missile_ammo > 0)
			{
			}
			break;
		}
	}
}

void Player::Update()
{
	if(RideType != Ride_type::foot)
		feul -= Time::deltaTime;

	if (feul < 0)
	{
		RideType = Ride_type::foot;
	}

	Movement();

	if (RideType == Ride_type::foot)
	{
		if (isshot)
		{
			switch (Anistate)
			{
			case T_Player_AniState::pistol_shot:
				Animation(L"a/pistol/Handgun_Walk ", 3, 0.1f, 1);
				break;
			case T_Player_AniState::machinegun_shot:
				Animation(L"a/AR/AR_attack ", 3, 0.1f, 2);
				break;

			}
		}
		else
		{
			switch (shot_type)
			{
			case P_shot_type::pistol:
				Animation(L"a/pistol/Handgun_Walk ", 3, 0.1f, 3);
				break;
			case P_shot_type::machine_gun:
				Animation(L"a/Walk/AR_walk ", 3, 0.1f, 4);
				break;
			case  P_shot_type::youdo_missle:
				break;
			}
		}
	}
	else if (RideType == Ride_type::kickboard)
	{
		Animation(L"k/Kickboard ", 4, 0.05f, 5);
	}
	else if (RideType == Ride_type::motercycle)
	{
		Animation(L"m/MotorCycle ", 4, 0.07f, 6);
	}
	else if (RideType == Ride_type::horse)
	{
		Animation(L"h/Horse ", 5, 0.07f, 7);
	}


	if (DXUTWasKeyPressed('1'))
	{
		shot_type = P_shot_type::pistol;
		RideType = Ride_type::foot;
	}
	if (DXUTWasKeyPressed('2'))
		shot_type = P_shot_type::machine_gun;
	if (DXUTWasKeyPressed('3'))
		shot_type = P_shot_type::youdo_missle;
	if (DXUTWasKeyPressed('4'))
		RideType = Ride_type::kickboard;
	if (DXUTWasKeyPressed('5'))
		RideType = Ride_type::motercycle;
	if (DXUTWasKeyPressed('6'))
		RideType = Ride_type::horse;
}

void Player::isHit()
{
	cout << "PLAYER HIT!!!!!!!" << endl;
}

void Player::Shot()
{
}
