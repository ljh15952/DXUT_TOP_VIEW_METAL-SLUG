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

	dieeft = new Sprite;
	dieeft->_position = { 640,360 };
	dieeft->isUI = true;
	dieeft->_layer = 1;
	dieeft->_scale = { 1.5,1.5f };


	RideType = Ride_type::foot;
	Hp = 3;
	Speed = 10;
	isJump = false;
	jumpTimer = 1;

	shot_type = P_shot_type::pistol;
	_mytype = T_My_Type::player;

	machine_gun_ammo = 500; //
	youdo_missile_ammo = 100;
	shot_timer = 0.3f;

	iscol = false;
	isshot = false;
	isoil = false;

	feul = 0;

	speedLimit = 10;

	Anistate = T_Player_AniState::pistol_walk;
	cameraaddnum = 0.2f;
	hittimer = 0.1f;

	ishit = false;
	vis = false;
	isdie = false;
	bisnum = 0;
}

Player::~Player()
{
	delete ShotPos;
	delete dieeft;
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
		if (DXUTIsKeyDown(VK_SPACE))
		{
			if(Speed>0)
				Speed-= cameraaddnum + 0.3f;
		}
		else
		{
			if (isoil)
			{
				if (Speed > 5)
					Speed -= cameraaddnum;
				if (Speed < 3)
					Speed+= cameraaddnum;
			}
			else
			{
				if (Speed < speedLimit)
					Speed+= cameraaddnum + 0.3f;
				if(Speed>speedLimit)
					Speed -= cameraaddnum + 0.3f;
			}
		}
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
			jumpTimer = 1;
		}
		if (jumpTimer < 0.5f)
		{
			if (Speed > speedLimit)
				Speed-= cameraaddnum;
		}
		else
		{
			if (Speed < speedLimit+5)
				Speed+= cameraaddnum;
		}
	}




	_position += v * Speed;

	ShotPos->_position = _position + v * 35;

	GM::GetInstance()->SetCameraUpdate(Speed);
}

void Player::Attack()
{
	shot_timer -= Time::deltaTime;
	if (shot_timer < 0)
	{
		switch (shot_type)
		{
		case P_shot_type::pistol:
			Bullet_Manager::GetInstance()->Shot_Bullet(ShotPos->_position, v,_mytype, shot_type);
			shot_timer = 0.3f;
			Anistate = T_Player_AniState::pistol_shot;
			break;
		case P_shot_type::machine_gun:
			Anistate = T_Player_AniState::machinegun_shot;
			if (machine_gun_ammo > 0)
			{
				Bullet_Manager::GetInstance()->Shot_Bullet(ShotPos->_position, { v.x,v.y }, _mytype, shot_type);
				machine_gun_ammo--;
				GM::GetInstance()->SetMachineGunLabel(machine_gun_ammo);
				shot_timer = 0.05f;
			}
			break;
		case P_shot_type::youdo_missle:
			if (youdo_missile_ammo > 0)
			{
				Bullet_Manager::GetInstance()->Shot_Bullet(ShotPos->_position, { v.x,v.y }, _mytype, shot_type);
				youdo_missile_ammo--;
				GM::GetInstance()->SetYoudoGunLabel(youdo_missile_ammo);
				shot_timer = 0.5f;
			}
			break;
		}
	}
}

void Player::Update()
{
	if (isdie)
	{
		dieeft->Animation(L"explose/Explosion ", 4, 0.15f, 18);
		if (Animation(L"a/die/Die ", 3, 0.2f, 17))
		{
			dieeft->_visible = false;
			_visible = false;
			isdie = false;
		}
		return;
	}

	if (!GM::GetInstance()->isgamestart)
		return;
	if(RideType != Ride_type::foot)
		feul -= Time::deltaTime;

	
	if (ishit)
	{
		GM::GetInstance()->isshake = !GM::GetInstance()->isshake;
		hittimer -= Time::deltaTime;
		if (hittimer < 0)
		{
			_visible = vis;
			vis = !vis;
			bisnum++;
			hittimer = 0.1f;
			if (bisnum > 9)
			{
				bisnum = 0;
				ishit = false;
			}
		}
	}

	if (feul < 0)
	{
		RideType = Ride_type::foot;
	}

	Movement();

	if (RideType == Ride_type::foot)
	{
		speedLimit = 10;
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
		speedLimit = 12;
		Animation(L"k/Kickboard ", 4, 0.05f, 5);
	}
	else if (RideType == Ride_type::motercycle)
	{
		speedLimit = 14;
		Animation(L"m/MotorCycle ", 4, 0.07f, 6);
	}
	else if (RideType == Ride_type::horse)
	{
		speedLimit = 13;
		Animation(L"h/Horse ", 5, 0.07f, 7);
	}
	else if (RideType == Ride_type::kickboard)
	{
		speedLimit = 13;
		Animation(L"k/Kickboard ", 4, 0.07f, 17);
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
}

void Player::isHit()
{
	if (ishit)
		return;

	ishit = true;
	Hp--;
	UI::GetInstance()->SetHpUI(Hp);
	if (Hp <= 0)
	{
		isdie = true;
		GM::GetInstance()->isgamestart = false;
	}
}

void Player::Shot()
{
}
