#include "DXUT.h"
#include "Player.h"

Player::Player(wstring path, Ride_type rt)
{
	Create(path);
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


	Hp = 3;
	Speed = 10;
	jumpTimer = 1;
	feul = 0;
	speedLimit = 10;

	RideType = rt;
	shot_type = P_shot_type::pistol;
	_mytype = T_My_Type::player;

	machine_gun_ammo = 500;
	youdo_missile_ammo = 100;
	shot_timer = 0.3f;

	isJump = false;
	iscol = false;
	isshot = false;
	isoil = false;
	ishit = false;
	vis = false;
	isdie = false;

	bisnum = 0;


	cameraaddnum = 0.2f;
	hittimer = 0.1f;

}

Player::~Player()
{
	delete ShotPos;
	delete dieeft;
}

void Player::Movement()
{
	iscol = false;
	if (GM::GetInstance()->stagenum == 1)
	{
		if ((_position.x >= 7518 || _position.y >= 7169) || (_position.x <= 0 || _position.y <= 0))
		{
			_position -= v * (Speed + 0.1f);
			iscol = true;
		}
		v = { (float)Director::GetInstance()->p.x - 640,(float)Director::GetInstance()->p.y - 360 };
	}
	else if(GM::GetInstance()->stagenum == 2)
	{
		if ((_position.x >= 6500 * 2.5f || _position.y >= (720*2.5f) - 550) || (_position.x <= 0 || _position.y <= 550))
		{
			_position -= v * (Speed + 0.1f);
			iscol = true;
		}
		v = { (float)Director::GetInstance()->p.x - 640 + 500,(float)Director::GetInstance()->p.y - 360 };
	}
	else if (GM::GetInstance()->stagenum == 3)
	{
		if ((_position.x >= 13000 * 2.5f || _position.y >= (720 * 2.5f)+550) || (_position.x <= 0 || _position.y <= 550))
		{
			_position -= v * (Speed + 0.1f);
			iscol = true;
		}
		v = { (float)Director::GetInstance()->p.x - 640 + 500,(float)Director::GetInstance()->p.y - 360 };
	}

	_rotation = atan2(v.y, v.x);

	float l = sqrt(v.x * v.x + v.y * v.y);
	v.x /= l;
	v.y /= l;


	if (!isJump)
	{
		if (DXUTIsKeyDown(VK_SPACE))
		{
			if (Speed > 0) 
				Speed -= cameraaddnum + 0.3f;
		}
		else
		{
			if (isoil)
			{
				if (Speed > 5)
					Speed -= cameraaddnum;
				if (Speed < 3)
					Speed += cameraaddnum;
			}
			else
			{
				if (Speed < speedLimit)
					Speed += cameraaddnum + 0.3f;
				if (Speed > speedLimit)
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
			isJump = false;
			jumpTimer = 1;
		}
		if (jumpTimer < 0.5f)
		{
			if (Speed > speedLimit)
				Speed -= cameraaddnum;
		}
		else
		{
			if (Speed < speedLimit + 5)
				Speed += cameraaddnum;
		}
	}




	_position += v * Speed * Time::deltaTime * 50;

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
			Shot_pistol();
			break;
		case P_shot_type::machine_gun:
			Shot_Machine();
			break;
		case P_shot_type::youdo_missle:
			Shot_Youdo();
			break;
		}
	}
}

void Player::Update()
{
	if (isdie)
	{
		StartDieAnimation();
		return;
	}

	if (!GM::GetInstance()->isgamestart)
		return;

	if(GM::GetInstance()->stagenum ==1)
		Feul_Manage();

	if (ishit)
		Invincible_time();

	if (GM::GetInstance()->stagenum == 2)
	{
		RideType = boat_ride;
	}

	Movement();
	SetPlayerAnimation();

	Change_Shot_Type();
}

void Player::isHit()
{
	if (ishit)
		return;

	ishit = true;

	//UI::GetInstance()->SetHpUI(--Hp);

	if (Hp <= 0);
		//isdie = true;
}

void Player::Invincible_time()
{
	GM::GetInstance()->isshake = !GM::GetInstance()->isshake; //카메라 흔들기

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

void Player::StartDieAnimation()
{
	dieeft->Animation(L"explose/Explosion ", 4, 0.15f, 18);
	if (Animation(L"a/die/Die ", 3, 0.2f, 17))
	{
		dieeft->_visible = false;
		_visible = false;
		isdie = false;
		GM::GetInstance()->isgamestart = false;
	}
}

void Player::SetPlayerAnimation() //update
{
	if (RideType == Ride_type::foot)
		isshot ? P_Foot_Atk_Ani() : P_Foot_Move_Ani();
	else
		Set_P_Ride_Ani();
}

void Player::Set_P_Foot_State()
{
	speedLimit = 10;
	RideType = foot;
}

void Player::Set_P_MotorCycle_State()
{
	speedLimit = 14;
	RideType = motercycle;
}

void Player::Set_P_Horse_State()
{
	speedLimit = 13;
	RideType = horse;
}

void Player::Set_P_KickBoard_State()
{
	speedLimit = 12;
	RideType = kickboard;
}

void Player::AddFeul()
{
	if (RideType != foot)
		feul = 10;
}

void Player::P_Foot_Move_Ani()
{
	cout << "ASDASD" << endl;
	switch (shot_type)
	{
	case P_shot_type::pistol:
		Animation(L"a/pistol/Handgun_Walk ", 3, 0.1f, 3);
		break;
	case P_shot_type::machine_gun:
		Animation(L"a/Walk/AR_walk ", 3, 0.1f, 4);
		break;
	case  P_shot_type::youdo_missle:
		Animation(L"a/Walk/AR_walk ", 3, 0.1f, 4);
		break;
	}
}

void Player::P_Foot_Atk_Ani()
{
	switch (shot_type)
	{
	case P_shot_type::pistol:
		Animation(L"a/pistol/Handgun_Walk ", 3, 0.1f, 1);
		break;
	case P_shot_type::machine_gun:
		Animation(L"a/AR/AR_attack ", 3, 0.1f, 2);
		break;
	}
}

void Player::Set_P_Ride_Ani()
{
	switch (RideType)
	{
	case kickboard:
		Animation(L"k/Kickboard ", 4, 0.05f, 5);
		break;
	case motercycle:
		Animation(L"m/MotorCycle ", 4, 0.07f, 6);
		break;
	case horse:
		Animation(L"h/Horse ", 5, 0.07f, 7);
		break;
	case boat_ride :
		Animation(L"w/w", 8, 0.07f, 27);
		break;
	case fly:
		Create(L"f.png");
		break;
	}
}

void Player::Change_Shot_Type()
{
	if (DXUTWasKeyPressed('1'))
	{
		shot_type = P_shot_type::pistol;
		if(GM::GetInstance()->stagenum==1)
			RideType = Ride_type::foot;
	}
	if (DXUTWasKeyPressed('2'))
		shot_type = P_shot_type::machine_gun;
	if (DXUTWasKeyPressed('3'))
		shot_type = P_shot_type::youdo_missle;
}

void Player::Shot_pistol()
{
	Bullet_Manager::GetInstance()->Shot_Bullet(ShotPos->_position, v, _mytype, shot_type);
	shot_timer = 0.3f;
}

void Player::Shot_Machine()
{
	if (machine_gun_ammo > 0)
	{
		Bullet_Manager::GetInstance()->Shot_Bullet(ShotPos->_position, { v.x,v.y }, _mytype, shot_type);
		machine_gun_ammo--;
		GM::GetInstance()->SetMachineGunLabel(machine_gun_ammo);
		shot_timer = 0.05f;
	}
}

void Player::Shot_Youdo()
{
	if (youdo_missile_ammo > 0)
	{
		Bullet_Manager::GetInstance()->Shot_Bullet(ShotPos->_position, { v.x,v.y }, _mytype, shot_type);
		youdo_missile_ammo--;
		GM::GetInstance()->SetYoudoGunLabel(youdo_missile_ammo);
		shot_timer = 0.5f;
	}
}

void Player::Feul_Manage()
{
	if (RideType != Ride_type::foot)
		feul -= Time::deltaTime;
	if (feul < 0)
	{
		RideType = Ride_type::foot;
	}
}
