#include "DXUT.h"
#include "ShotEnemy.h"
#include "Bullet.h"
ShotEnemy::ShotEnemy(Player* p)
{
	Create(L"E/Yakuza 1/Attack/A1.png");
	Hp = 1;
	player = p;
	_mytype = shot_enemy;
	isDie = false;
	DieAnipath = L"E/Yakuza 1/Die/d";
}

ShotEnemy::~ShotEnemy()
{
}

void ShotEnemy::Attack()
{
}

void ShotEnemy::Movement()
{
}

void ShotEnemy::Update()
{
	if (!GM::GetInstance()->isgamestart || !_visible)
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
		GoTo(player->_position, 0);

		vector2 v = { player->_position.x - _position.x , player->_position.y - _position.y };
		float l = sqrt(v.x * v.x + v.y * v.y);
		v.y /= l;
		v.x /= l;
		if (l < 1000)
		{
			static float timer = 1;
			timer -= Time::deltaTime;
			if (timer < 0)
			{
				Bullet_Manager::GetInstance()->Shot_Bullet(_position, v, T_My_Type::shot_enemy, pistol);
				timer = 1;
			}
		}
	}
}

void ShotEnemy::isHit()
{
	Hp--;
	if (Hp < 0)
	{
		isDie = true;
	}
}
