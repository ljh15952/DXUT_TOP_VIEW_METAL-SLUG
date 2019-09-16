#pragma once
#include "Sprite.h"
class EnemyWeapon : public Sprite
{
public:
	EnemyWeapon();
	void Update() override; //���ڴ� ������ ������� �ڷ� ��������
};

class EnemyWeaponManager : public Singleton<EnemyWeaponManager>
{
public:
	void MakeEnemyWeapons();
	void EnemyShot();
	void DeleteEnemyWeapons();
};

