#pragma once
#include "Sprite.h"
#include "Obj.h"
class Bullet :
	public Sprite
{
public:
	Bullet();
	~Bullet();
	void Update() override;
	vector2 _v;
	T_My_Type _mytype;
	void SetBullet();
	bool isHit;
	wstring DieAnipath;
	float timer;
	P_shot_type _my_shot_type;

	Sprite * youdosp;

	void CollideBullet(Obj* obj);
	void shot_youdo();
	bool isScreenOut();
	void StartBombAni();
	void P_Movement();
	void E_Movement();
	void CommonBulletMove();
	void YoudoBulletMove();
	float GetDistance(Sprite * Target);
};

class Bullet_Manager : public Singleton<Bullet_Manager>
{
public:
	void Make_Bullet();
	void Shot_Bullet(vector2 startpos, vector2 v, T_My_Type mt, P_shot_type shottype);
	void Delete_Bullet();
	list<Bullet*> _bullets;
};

