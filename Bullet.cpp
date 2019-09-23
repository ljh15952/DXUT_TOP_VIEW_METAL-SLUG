#include "DXUT.h"
#include "Bullet.h"
#include "Enemy_1.h"
Bullet::Bullet()
{
	Create(L"N_A.png");
	_visible = false;
	isHit = false;
	timer = 10;
	youdosp = nullptr;
}

Bullet::~Bullet()
{
	delete youdosp;
}

void Bullet::Update()
{
	if (isScreenOut())
		_visible = false;

	if (!_visible)
		return;

	if (isHit)
		StartBombAni();
	else
		_mytype == T_My_Type::enemy ? E_Movement() : P_Movement(); //내타입이 적총알이면 E_move 아니면 P_move
}



bool Bullet::isScreenOut()
{
	if ((_position.x >= 9850 || _position.y >= 9850) || (_position.x <= 0 || _position.y <= 0))
		return true;
	return false;
}

void Bullet::StartBombAni()
{
	_scale = { 3,3 };
	if (Animation(DieAnipath, 4, 0.075f, 2))
	{
		isHit = false;
		_visible = false;
		youdosp = nullptr;
	}
	return;
}

void Bullet::P_Movement()
{
	_my_shot_type != P_shot_type::youdo_missle ? CommonBulletMove() : YoudoBulletMove();
}

void Bullet::E_Movement()
{
	timer -= Time::deltaTime;
	if (timer < 0)
	{
		isHit = true;
		timer = 10;
	}
}

void Bullet::CommonBulletMove()
{
	_position += _v * 30;
}
//쓰래기하고 적총알하고 맞으면 없어지는듯
void Bullet::YoudoBulletMove()
{
	if (youdosp == nullptr)
	{
		for (auto it : EnemyManager::GetInstance()->_enemys)
		{
			if (it->_visible && !it->isDie)
			{
				if (GetDistance(it) < 900)
					youdosp = it;
			}
		}
	}

	youdosp == nullptr ? isHit = true : shot_youdo();
}

void Bullet::shot_youdo()
{
	if (GoTo(youdosp->_position, 1000)) //맞았을떄 들어가는 if문
	{
		isHit = true;
	}
}

float Bullet::GetDistance(Sprite* Target)
{
	vector2 v = { Target->_position.x - _position.x,Target->_position.y - _position.y };
	return sqrt(v.x * v.x + v.y * v.y);
}

void Bullet::CollideBullet(Obj* obj)
{
	RECT TEMP;
	if (!IntersectRect(&TEMP, &GetRect(), &obj->GetRect()))
		return;
	if (obj->_mytype == _mytype)
		return;
	obj->isHit();
	isHit = true;
}

void Bullet::SetBullet()
{
	switch (_mytype)
	{
	case player:
		_my_shot_type == youdo_missle ? Create(L"S_A.png") : Create(L"N_A.png");
		break;
	case enemy:
		Create(L"E/w/Mine.png");
		break;
	}

	DieAnipath = L"explose/Explosion ";
}




void Bullet_Manager::Make_Bullet()
{
	for (int i = 0; i < 500; i++)
	{
		Bullet* b = new Bullet();
		_bullets.push_back(b);
	}
}

void Bullet_Manager::Shot_Bullet(vector2 startpos, vector2 v, T_My_Type mt, P_shot_type shottype)
{
	for (auto it : _bullets)
	{
		if (!it->_visible)
		{
			it->_position = startpos;
			it->_v = v;
			it->_rotation = atan2(v.y, v.x);
			it->_mytype = mt;
			it->_scale = { 1,1 };
			it->_visible = true;
			it->_my_shot_type = shottype;
			it->SetBullet();
			return;
		}
	}
}
void Bullet_Manager::Delete_Bullet()
{
	for (auto it : _bullets)
		delete it;
	_bullets.clear();
}