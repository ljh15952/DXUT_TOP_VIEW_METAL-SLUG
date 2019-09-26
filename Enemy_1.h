#pragma once
#include "Obj.h"
#include "Types.h"
#include "Bullet.h"
class Enemy_1 : public Obj
{
public:
	Enemy_1();
	~Enemy_1();
	void Attack() override;
	void Movement() override;
	void Update() override;
	void isHit() override;

	Sprite* mini;

	void SetEnemy();

	bool isDie;

	float atktimer;
	vector2 GoPos;

	wstring MoveAnipath;
	wstring DieAnipath;

};

class EnemyManager : public Singleton<EnemyManager>
{
public:
	void Make_Enemy();
	void SetEnemy(vector2 pos, Ride_type rt);
	void Delete_Enemys();

	vector<Enemy_1*> _enemys;
};