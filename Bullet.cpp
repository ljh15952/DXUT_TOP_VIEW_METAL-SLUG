#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet()
{
	Create(L"N_A.png");
	_visible = false;
	isHit = false;
}

void Bullet::Update()
{
	if ((_position.x >= 9850 || _position.y >= 9850) || (_position.x <= 0 || _position.y <= 0))
		_visible = false;
	if (!_visible)
		return;
	if (isHit)
	{
		_scale = { 3,3 };
		if (Animation(DieAnipath, 4, 0.075f, 2))
		{
			isHit = false;
			_visible = false;
		}
	}


	if (_mytype == T_My_Type::player && !isHit)
		_position += _v * 30;
}

void Bullet::CollideBullet(Obj* obj)
{
	RECT TEMP;
	if (!IntersectRect(&TEMP, &GetRect(), &obj->GetRect()))
		return;
	if (obj->_mytype == _mytype)
		return;
	obj->isHit();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	//_visible = false;
	isHit = true;
}

void Bullet::SetBullet()
{
	if (_mytype == T_My_Type::enemy)
	{
		Create(L"E/w/Mine.png");
		DieAnipath = L"explose/Explosion ";
	}
	else
	{
		Create(L"N_A.png");
		DieAnipath = L"explose/Explosion ";
	}
}


void Bullet_Manager::Make_Bullet()
{
	for (int i = 0; i < 500; i++)
	{
		Bullet* b = new Bullet();
		_bullets.push_back(b);
	}
}

void Bullet_Manager::Shot_Bullet(vector2 startpos, vector2 v, T_My_Type mt)
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