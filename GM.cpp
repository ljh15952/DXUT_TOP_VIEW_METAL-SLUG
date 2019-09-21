#include "DXUT.h"
#include "GM.h"
#include "Enemy_1.h"
void GM::GMInit()
{
	isgamestart = false;
	CameraSize = { 1280 * 10 / 6.5f, -720 * 10 / 6.5f };
	//CameraSize = { 1280 *1.3f , -720*1.3f };
	KillPoint = 0;
}

void GM::SpawnEnemy(int missionnum)
{
	switch (missionnum)
	{
	case 2:
		for (int i = 0; i < 3; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::horse);
		}
		break;
	case 3:
		for (int i = 0; i < 3; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::motercycle);
		}
		break;
	case 4:
		for (int i = 0; i < 3; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::horse);
		}
		for (int i = 0; i < 3; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::motercycle);
		}
		for (int i = 0; i < 3; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::foot);
		}
		break;
	case 5:
		cout << "CLEAR!!!!!!!" << endl;
		isgamestart = false;
		break;
	}
}

void GM::SetCameraUpdate(float Speed)
{
	if (Speed > 9.5f)
		CameraSize = { 1280 * Speed / 6.5f, -720 * Speed / 6.5f };
}

void GM::SetNextMission()
{
	if (KillPoint == 2)
	{
		//mission2
		//말타는 야쿠자 3명소환
		SpawnEnemy(2);
	}
	else if (KillPoint == 5)
	{
		//mission3
		//오토바이 탄 야쿠자 3명 소환
		SpawnEnemy(3);

	}
	else if (KillPoint == 8)
	{
		//mission4
		//야쿠자 10명소환
		SpawnEnemy(4);

	}
	else if (KillPoint == 17)
	{
		//mision5
		SpawnEnemy(5);
		//하천까지 이동
	}
}
