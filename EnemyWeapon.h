#pragma once
#include "Sprite.h"
class EnemyWeapon : public Sprite
{
public:
	EnemyWeapon();
	void Update() override; //지뢰는 가만히 쓰래기는 뒤로 굴러가기
};

class EnemyWeaponManager : public Singleton<EnemyWeaponManager>
{
public:
	void MakeEnemyWeapons();
	void EnemyShot();
	void DeleteEnemyWeapons();
};

