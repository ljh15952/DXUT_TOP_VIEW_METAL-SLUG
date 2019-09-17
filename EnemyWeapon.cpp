#include "DXUT.h"
#include "EnemyWeapon.h"

EnemyWeapon::EnemyWeapon()
{
	Create(L"UFO_1.png");
	_visible = false;
}

void EnemyWeapon::Update()
{
	if (!_visible)
		return;

	_position += -v;
}

void EnemyWeaponManager::MakeEnemyWeapons()
{
	for (int i = 0; i < 1000; i++)
	{
		EnemyWeapon* b = new EnemyWeapon();
		_weapons.push_back(b);
	}
}

void EnemyWeaponManager::EnemyShot(vector2 startpos, vector2 v)
{
	for (auto it : _weapons)
	{
		if (!it->_visible)
		{
			it->_position = startpos;
			it->v = v;
			it->_visible = true;
			return;
		}
	}
}

void EnemyWeaponManager::DeleteEnemyWeapons()
{
	for (auto it : _weapons)
		delete it;
	_weapons.clear();
}
