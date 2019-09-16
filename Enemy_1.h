#pragma once
#include "Obj.h"
class Enemy_1 : public Obj
{
public:
	Enemy_1(Ride_type RideT);
	void Attack() override;
	void Movement() override;
	void Update() override;
	
	float timer[4];
	float atktimer;
};

