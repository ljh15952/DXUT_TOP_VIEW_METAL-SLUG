#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet()
{
	Create(L"Weapon.png");
	_scale = { 0.5f,0.5f };
	_visible = false;
}

void Bullet::Update()
{
	if (!_visible)
		return;

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
	_visible = false;
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
			it->_visible = true;
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