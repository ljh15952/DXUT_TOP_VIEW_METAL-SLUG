#include "DXUT.h"
#include "Enemy_1.h"
#include "GM.h"

Enemy_1::Enemy_1()
{
	_scale = { 1.7f,1.7f };
	_visible = false;

	mini = new Sprite;
	mini->_visible = false;
	mini->_scale = { 0.5f,0.5f };
	mini->isUI = true;
	mini->_layer = 5;

	
	v = { 1,0 };


	_mytype = T_My_Type::enemy;
	atktimer = 3;
	Hp = 1;
	isDie = false;
}

Enemy_1::~Enemy_1()
{
	delete mini;
}

void Enemy_1::Attack()
{
	atktimer -= Time::deltaTime;
	if (atktimer < 0)
	{
		Bullet_Manager::GetInstance()->Shot_Bullet(_position, v, _mytype,P_shot_type::pistol);
		atktimer = 3.5f;
	}
	//지뢰나 쓰래기 던지기
}

void Enemy_1::Movement()
{
	if (GoTo({ GoPos + (v*2300) }, 100 * Speed))
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
	if (!_visible || !GM::GetInstance()->isgamestart)
		return;
	
	if (isDie)
	{
		if (Animation(DieAnipath, 4, 0.2f, 2))
		{
			isDie = false;
			_visible = false;
		}
	}
	else
	{
		Attack();
		Movement();
		Animation(MoveAnipath, 4, 0.1f, 1);
	}

}	

void Enemy_1::isHit()
{
	Hp--;
	if (Hp < 0)
	{
		isDie = true;
		mini->_visible = false;
		GM::GetInstance()->KillPoint++;
		GM::GetInstance()->SetNextMission();
		GM::GetInstance()->minusenemycount();
	}
}

void Enemy_1::SetEnemy()
{
	switch (RideType)
	{
	case Ride_type::foot:
		MoveAnipath = L"E/Yakuza 1/Walk/w";
		DieAnipath = L"E/Yakuza 1/Die/d";
		Speed = 3;
		break;
	case Ride_type::horse:
		MoveAnipath = L"E/Yakuza 2/Walk 2/w";
		DieAnipath = L"E/Yakuza 2/Die 2/d";
		Speed = 5;
		break;
	case Ride_type::motercycle:
		MoveAnipath = L"E/Yakuza 3/Walk 3/w";
		DieAnipath = L"E/Yakuza 3/Die 3/d";
		Speed = 6;
		break;
	}
	Create(MoveAnipath + L"1.png");
	mini->Create(MoveAnipath + L"1.png");
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
			it->SetEnemy();
			return;
		}
	}
}

void EnemyManager::Delete_Enemys()
{
	for (auto it : _enemys)
	{
		delete it;
		cout << "ASDASD" << endl;
	}
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
