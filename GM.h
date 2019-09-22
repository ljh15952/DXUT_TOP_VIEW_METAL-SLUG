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

	bool isgamestart;
	vector2 CameraSize;
	int KillPoint;

	Label* timer;
	float time;

	bool isshake;

};

