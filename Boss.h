#pragma once
#include "Obj.h"
#include "Player.h"
class Boss :
	public Obj
{
public:
	Boss(Player* p);
	~Boss();
	void Attack() override;
	void Movement() override;
	void Update() override;
	void isHit() override;

	bool isDie;
	Player* player;
	wstring MoveAnipath;
	wstring DieAnipath;

	float shottimer;

	void P1();
	void P2();
	void P3();

	float rad;
};

