#pragma once
#include "Obj.h"
#include "EnemyWeapon.h"
class Enemy_1 : public Obj
{
public:
	Enemy_1(Ride_type RideT);
	void Attack() override;
	void Movement() override;
	void Update() override;
	void isHit() override;

	float atktimer;
	vector2 GoPos;
};

