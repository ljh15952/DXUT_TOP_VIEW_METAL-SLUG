#include "DXUT.h"
#include "Enemy_1.h"

Enemy_1::Enemy_1(Ride_type RideT)
{
	RideType = RideT;

	switch (RideT)
	{
	case Ride_type::foot:
		//create(L"foot.png");
		Create(L"soldier1_gun.png");
		Speed = 7;
		break;
	case Ride_type::horse:
		//create(L"horse.png");

		break;
	case Ride_type::kickboard:
		//create(L"kickboard.png");

		break;
	case Ride_type::motercycle:
		//create(L"motercycle.png");
		break;
	}

	for (int i = 0; i < 4; i++)
	{
		timer[i] = 0;
	}
	timer[0] = 5;
	v = { 1,0 };


	_mytype = T_My_Type::enemy;
	atktimer = 3;
}

void Enemy_1::Attack()
{
	atktimer -= Time::deltaTime;
	if (atktimer < 0)
	{
		cout << "지뢰나 쓰래기 던지기!!" << endl;
		EnemyWeaponManager::GetInstance()->EnemyShot(_position, v);
		atktimer = 3.5f;
	}
	//지뢰나 쓰래기 던지기
}

void Enemy_1::Movement()
{
	for (int i = 0; i < 4; i++)
	{
		if (timer[i] > 0)
		{
			timer[i] -= Time::deltaTime;
			switch (i)
			{
			case 0:
				_position += v * Speed;
				if (timer[0] < 0)
				{
					timer[1] = 5;
					_rotation = -1.6f;
					v = { 0,-1 };
				}
				break;
			case 1:
				_position += v * Speed;
				if (timer[1] < 0)
				{
					timer[2] = 5;
					_rotation = 3.1f;
					v = { -1,0 };
				}
				break;
			case 2:
				_position += v * Speed;
				if (timer[2] < 0)
				{
					timer[3] = 5;
					_rotation = 1.55f;
					v = { 0,1 };
				}
				break;
			case 3:
				_position += v * Speed;
				if (timer[3] < 0)
				{
					timer[0] = 5;
					_rotation = 0;
					v = { 1,0 };
				}
				break;
			}
		}
	}

	//미로찾기 알고리즘을 써야되나?

}

void Enemy_1::Update()
{
	Attack();
	Movement();
}

void Enemy_1::isHit()
{
	cout << "ENEMY HIT!!" << endl;
}
