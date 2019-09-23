#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "UI.h"
class Player : public Obj
{
public:
	Player();
	~Player();
	void Movement() override;
	void Attack() override;
	void Update() override;
	void isHit() override;

	Sprite* ShotPos;
	Sprite* dieeft;

	P_shot_type shot_type;

	void Invincible_time();
	void StartDieAnimation();
	void SetPlayerAnimation();
	void Set_P_Foot_State();
	void Set_P_MotorCycle_State();
	void Set_P_Horse_State();
	void Set_P_KickBoard_State();
	void AddFeul();
	void P_Foot_Move_Ani();
	void P_Foot_Atk_Ani();
	void Set_P_Ride_Ani();
	void Change_Shot_Type();
	void Shot_pistol();
	void Shot_Machine();
	void Shot_Youdo();
	void Feul_Manage();

	bool isJump;
	bool iscol;
	bool isshot;
	bool isoil;
	bool ishit;
	bool vis;
	bool isdie;

	float jumpTimer;
	float shot_timer;
	float feul;
	float cameraaddnum;
	float hittimer;

	int machine_gun_ammo;
	int youdo_missile_ammo;
	int speedLimit;
	int bisnum;
};

