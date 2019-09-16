#pragma once
#include "Obj.h"
#include "Bullet.h"
class Player : public Obj
{
public:
	Player();
	void Movement() override;
	void Attack() override;
	void Update() override;

	Sprite* ShotPos;

	vector2 v;
	bool isJump;
	float jumpTimer;

	P_shot_type shot_type;

	int machine_gun_ammo;
	int youdo_missile_ammo;

	float shot_timer;
};

