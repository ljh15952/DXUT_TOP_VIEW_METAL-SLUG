#pragma once
#include "Sprite.h"
class Obj : public Sprite
{
public:
	virtual void Movement() {};
	virtual void Attack() {};
	virtual void isHit() {};

	//status
	int Hp;
	float Speed;

	Ride_type RideType;
	
	T_My_Type _mytype;

	vector2 v;
};

