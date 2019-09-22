#pragma once
#include "Types.h"
#include "Label.h"
class GM : public Singleton<GM>
{
public:
	void GMInit();
	void SpawnEnemy(int missionnum);
	void SetCameraUpdate(float Speed);
	void SetNextMission();

	void UpdateTimer();
	void countEnemy();
	void minusenemycount();

	void SetMachineGunLabel(int a);
	void SetYoudoGunLabel(int a);


	bool isgamestart;
	vector2 CameraSize;
	int KillPoint;

	Label* timer;
	float time;

	Label* EnemyRemainLabel;
	int howmanyenemy;

	Label* remainpistol;
	Label* remainmachine;
	Label* remainyoudo;

	bool isshake;

};

