#include "DXUT.h"
#include "BoatEnemy.h"

BoatEnemy::BoatEnemy()
{
	Create(L"Yakuza 5/Idle/i1.png");
	Hp = 3;
	_mytype = shot_enemy;
	isDie = false;
	_scale = { 2,2 };
	_visible = false;
	DieAnipath = L"explose/Explosion ";
}

BoatEnemy::~BoatEnemy()
{
}

void BoatEnemy::Attack()
{
	static float t1 = 1;
	t1 -= Time::deltaTime;
	if (t1 < 0)
	{
		Bullet_Manager::GetInstance()->Shot_Bullet(_position, { -1,0.1f }, shot_enemy, pistol);
		Bullet_Manager::GetInstance()->Shot_Bullet(_position, { -1,0 }, shot_enemy, pistol);
		Bullet_Manager::GetInstance()->Shot_Bullet(_position, { -1,-0.1f }, shot_enemy, pistol);

		t1 = 3;
	}
}

void BoatEnemy::Movement()
{
	_position.x += 3;
}

void BoatEnemy::Update()
{
	if (isDie)
	{
		if (Animation(DieAnipath, 4, 0.2f, 3))
		{
			isDie = false;
			_visible = false;
		}
	}
	else
	{
		Movement();
		Attack();
		Animation(L"Yakuza 5/Idle/i", 4, 0.2f, 2);
	}
}

void BoatEnemy::isHit()
{
	cout << "SADSDSDAS" << endl;
	Hp--;
	if (Hp < 0)
	{
		isDie = true;
	}
}

void BoatEnemyManager::Make_Enemy()
{
	for (int i = 0; i < 50; i++)
	{
		BoatEnemy* E = new BoatEnemy();
		_enemys.push_back(E);
	}
}

void BoatEnemyManager::SetEnemy(vector2 pos)
{
	for (auto it : _enemys)
	{
		if (!it->_visible && !it->isDie)
		{
			it->_position = pos;
			it->_visible = true;
			return;
		}
	}
}

void BoatEnemyManager::Delete_Enemys()
{
	for (auto it : _enemys)
	{
		delete it;
	}
	_enemys.clear();
}
