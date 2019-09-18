#include "DXUT.h"
#include "Enemy_1.h"

//enemy manager 화

Enemy_1::Enemy_1()
{
	_scale = { 1.7f,1.7f };
	_visible = false;
	Create(L"E/Walk/w1.png");

	mini = new Sprite;
	mini->Create(L"E/Walk/w1.png");
	mini->_visible = false;
	mini->_scale = { 0.5f,0.5f };
	mini->isUI = true;
	mini->_layer = 5;

	//switch (RideT)
	//{
	//case Ride_type::foot:
	//	//create(L"foot.png");
	//	Create(L"E/Walk/w1.png");
	//	Speed = 7;
	//	break;
	//case Ride_type::horse:
	//	//create(L"horse.png");

	//	break;
	//case Ride_type::kickboard:
	//	//create(L"kickboard.png");

	//	break;
	//case Ride_type::motercycle:
	//	//create(L"motercycle.png");
	//	break;
	//}

	v = { 1,0 };


	_mytype = T_My_Type::enemy;
	atktimer = 3;
	Hp = 3;
	isDie = false;
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
	cout << 100 * (rand() % 5 + 3) << endl;
	if (GoTo({ GoPos + (v*2300) }, 100 * (rand()%5+5)))
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
	if (!_visible)
		return;
	
	if (isDie)
	{
		if (Animation(L"E/Die/d", 4, 0.2f, 2))
		{
			isDie = false;
			_visible = false;
		}
	}
	else
	{
		//	Attack();
		Movement();
		Animation(L"E/Walk/w", 4, 0.1f, 1);
	}

}	

void Enemy_1::isHit()
{
	Hp--;
	if (Hp < 0)
	{
	//	_visible = false;
		isDie = true;
		mini->_visible = false;
	}
	cout << "ENEMY HIT!!" << endl;
}


void EnemyManager::Make_Enemy()
{
	for (int i = 0; i < 30; i++)
	{
		Enemy_1* E = new Enemy_1;
		_enemys.push_back(E);
	}
}

void EnemyManager::SetEnemy(vector2 pos, Ride_type rt)
{
	for (auto it : _enemys)
	{
		if (!it->_visible)
		{
			it->_position = pos;
			it->RideType = rt;
			it->GoPos = pos;
			it->_visible = true;
			it->mini->_visible = true;
			return;
		}
	}
}

void EnemyManager::Delete_Enemys()
{
	for (auto it : _enemys)
		delete it;
	_enemys.clear();
}

void EnemyManager::SetOff_Enemy(Enemy_1* e)
{
	for (auto it : _enemys)
	{
		if (it == e)
		{
			it->_visible = false;
		}
	}
}
