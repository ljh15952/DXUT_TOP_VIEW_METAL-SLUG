#pragma once
#include "Sprite.h"
class EnemyWeapon : public Sprite
{
public:
	EnemyWeapon();
	void Update() override; //���ڴ� ������ ������� �ڷ� ��������

	vector2 v;
};

class EnemyWeaponManager : public Singleton<EnemyWeaponManager>
{
public:
	void MakeEnemyWeapons();
	void EnemyShot(vector2 startpos, vector2 v);
	void DeleteEnemyWeapons();
	list<EnemyWeapon*> _weapons;
};

