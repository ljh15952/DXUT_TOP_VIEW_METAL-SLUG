#pragma once
#include "Sprite.h"
class Obj : public Sprite
{
public:
	virtual void Movement() {};
	virtual void Attack() {};


	//status
	int Hp;
	float Speed;

	Ride_type RideType;
	
	vector2 v;
};

