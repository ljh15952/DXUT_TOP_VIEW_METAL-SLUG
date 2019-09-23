#include "DXUT.h"
#include "GM.h"
#include "Enemy_1.h"
void GM::GMInit()
{
	isgamestart = false;
	CameraSize = { 1280 * 10 / 6.5f, -720 * 10 / 6.5f };
	//CameraSize = { 1280 *1.3f , -720*1.3f };
	KillPoint = 0;

	isshake = false;

	timer = new Label;
	timer->_position = { 640,100 };
	time = 60;

	EnemyRemainLabel = new Label;
	EnemyRemainLabel->_position = { 640,200 };
	howmanyenemy = 2;
	countEnemy();


	remainpistol = new Label;
	remainmachine = new Label;
	remainyoudo = new Label;

	remainpistol->_scale = { 0.7f,0.7f };
	remainpistol->_position = { 138,30 };
	remainpistol->Create_Label(10);

	remainmachine->_scale = { 0.7f,0.7f };
	remainmachine->_position = { 200,30 };
	remainmachine->Create_Label(0);

	remainyoudo->_scale = { 0.7f,0.7f };
	remainyoudo->_position = { 280,30 };
	remainyoudo->Create_Label(0);
}

void GM::SpawnEnemy(int missionnum)
{
	time = 60;
	switch (missionnum)
	{
	case 2:
		for (int i = 0; i < 5; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::horse);
			howmanyenemy++;
		}
		break;
	case 3:
		for (int i = 0; i < 5; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::motercycle);
			howmanyenemy++;

		}
		break;
	case 4:
		for (int i = 0; i < 4; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::horse);
			howmanyenemy++;

		}
		for (int i = 0; i < 4; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::motercycle);
			howmanyenemy++;

		}
		for (int i = 0; i < 4; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::foot);
			howmanyenemy++;

		}
		break;
	case 5:
		cout << "CLEAR!!!!!!!" << endl;
		isgamestart = false;
		break;
	}
	countEnemy();
}

void GM::SetCameraUpdate(float Speed)
{
	if (Speed > 9.5f)
	{
		CameraSize = { 1280 * Speed / 6.5f, -720 * Speed / 6.5f };

		if (isshake)
		{
			CameraSize = { 1330 * Speed / 6.5f, -770 * Speed / 6.5f };
		}
	}
}

void GM::SetNextMission()
{
	if (KillPoint == 2)
	{
		//mission2
		//말타는 야쿠자 5명소환
		SpawnEnemy(2);
	}
	else if (KillPoint == 7)
	{
		//mission3
		//오토바이 탄 야쿠자 5명 소환
		SpawnEnemy(3);

	}
	else if (KillPoint == 12)
	{
		//mission4
		//야쿠자 12명소환
		SpawnEnemy(4);

	}
	else if (KillPoint == 24)
	{
		//mision5
		SpawnEnemy(5);
		//하천까지 이동
	}
}

void GM::UpdateTimer()
{
	if (!isgamestart)
		return;
	time -= Time::deltaTime;
	if (time <= 0)
		isgamestart = false;
	timer->Create_Label(time);
}

void GM::countEnemy()
{
	EnemyRemainLabel->Create_Label(howmanyenemy);
}

void GM::minusenemycount()
{
	howmanyenemy--;
	countEnemy();
}

void GM::SetMachineGunLabel(int a)
{
	remainmachine->Create_Label(a);
}

void GM::SetYoudoGunLabel(int a)
{
    remainyoudo->Create_Label(a);
}

void GM::deleteLabel()
{
	timer->Delete_Label();
	delete timer;
	remainpistol->Delete_Label();
	delete remainpistol;
	remainmachine->Delete_Label();
	delete remainmachine;
	remainyoudo->Delete_Label();
	delete remainyoudo;
	EnemyRemainLabel->Delete_Label();
	delete EnemyRemainLabel;
}
