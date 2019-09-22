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
	time = 60;
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
		}
		break;
	case 3:
		for (int i = 0; i < 5; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::motercycle);
		}
		break;
	case 4:
		for (int i = 0; i < 4; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::horse);
		}
		for (int i = 0; i < 4; i++)
		{
			vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::motercycle);
		}
		for (int i = 0; i < 4; i++)
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
		//��Ÿ�� ������ 5���ȯ
		SpawnEnemy(2);
	}
	else if (KillPoint == 7)
	{
		//mission3
		//������� ź ������ 5�� ��ȯ
		SpawnEnemy(3);

	}
	else if (KillPoint == 12)
	{
		//mission4
		//������ 12���ȯ
		SpawnEnemy(4);

	}
	else if (KillPoint == 24)
	{
		//mision5
		SpawnEnemy(5);
		//��õ���� �̵�
	}
}

void GM::UpdateTimer()
{
	if (!isgamestart)
		return;
	time -= Time::deltaTime;
	if (time <= 0)
		isgamestart = false;
	timer->Create_Label(time, { 640,100 });
}
