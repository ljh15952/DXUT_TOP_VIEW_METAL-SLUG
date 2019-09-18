#include "DXUT.h"
#include "Enemy_1.h"

Enemy_1::Enemy_1(Ride_type RideT)
{
	RideType = RideT;
	_scale = { 1.7f,1.7f };

	switch (RideT)
	{
	case Ride_type::foot:
		//create(L"foot.png");
		Create(L"E/Walk/w1.png");
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


	if (GoTo({ GoPos + (v*2300) }, 500))
	{
		GoPos = _position;
		int num = rand() % 4; // 0,1,2,3

		if (_position.x > 8000)
			num = 3;
		else if(_position.x < 1000)
			num = 0;
		else if (_position.y < 1000)
			num = 1;
		else if (_position.y > 8000)
			num = 2;
		switch (num)
		{
		case 0:
			v = { 1,0 };
			break;
		case 1:
			v = { 0,1 };
			break;
		case 2:
			v = { 0,-1 };
			break;
		case 3:
			v = { -1,0 };
			break;
		}
	}

	//미로찾기 알고리즘을 써야되나?

}

void Enemy_1::Update()
{
	Attack();
	Movement();

	Animation(L"E/Walk/w", 4, 0.1f,1);
}	

void Enemy_1::isHit()
{
	cout << "ENEMY HIT!!" << endl;
}
