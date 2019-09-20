#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "UI.h"
class Player : public Obj
{
public:
	Player();
	void Movement() override;
	void Attack() override;
	void Update() override;
	void isHit() override;

	Sprite* ShotPos;


	bool isJump;
	float jumpTimer;

	P_shot_type shot_type;
	T_Player_AniState Anistate;

	void Shot();

	int machine_gun_ammo;
	int youdo_missile_ammo;

	float shot_timer;

	bool iscol;
	bool isshot;
	bool isoil;

	float feul;
};

