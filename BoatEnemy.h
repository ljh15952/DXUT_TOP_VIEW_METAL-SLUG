#pragma once
#include "Obj.h"
#include "Player.h"
class BoatEnemy :
	public Obj
{
public:
	BoatEnemy();
	~BoatEnemy();
	void Attack() override;
	void Movement() override;
	void Update() override;
	void isHit() override;

	bool isDie;
	Player* player;
	wstring MoveAnipath;
	wstring DieAnipath;
};

class BoatEnemyManager : public Singleton<BoatEnemyManager>
{
public:
	void Make_Enemy();
	void SetEnemy(vector2 pos);
	void Delete_Enemys();

	vector<BoatEnemy*> _enemys;
};