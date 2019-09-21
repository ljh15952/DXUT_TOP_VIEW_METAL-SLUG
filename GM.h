#pragma once
#include "Types.h"
class GM : public Singleton<GM>
{
public:
	void GMInit();
	void SpawnEnemy(int missionnum);
	void SetCameraUpdate(float Speed);
	void SetNextMission();

	bool isgamestart;
	vector2 CameraSize;
	int KillPoint;

};

