#pragma once
#include "Obj.h"
#include "Player.h"
class ShotEnemy :
	public Obj
{
public:
	ShotEnemy(Player * p);
	~ShotEnemy();
	void Attack() override;
	void Movement() override;
	void Update() override;
	void isHit() override;

	bool isDie;
	Player* player;
	wstring MoveAnipath;
	wstring DieAnipath;
};

