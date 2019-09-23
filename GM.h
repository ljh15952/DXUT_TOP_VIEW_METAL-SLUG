#pragma once
#include "Types.h"
#include "Label.h"

//남은 총알수는 여기서 세주고 UI에서 라벨 띄우기
//남은 적수는 여기서 세주고 라벨띄우는건 UI에서
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

	void deleteLabel();

	bool isshake;

};

