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
	
};

