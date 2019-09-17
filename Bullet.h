#pragma once
#include "Sprite.h"
#include "Obj.h"
class Bullet :
	public Sprite
{
public:
	Bullet();
	void Update() override;
	vector2 _v;
	void CollideBullet(Obj* obj);
	T_My_Type _mytype;
};

class Bullet_Manager : public Singleton<Bullet_Manager>
{
public:
	void Make_Bullet();
	void Shot_Bullet(vector2 startpos, vector2 v, T_My_Type mt);
	void Delete_Bullet();
	list<Bullet*> _bullets;
};

