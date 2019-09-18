#pragma once
#include "Sprite.h"
#include "Player.h"
#include "Enemy_1.h"
class MiniMap : public Sprite
{
public:
	MiniMap(Player* p, vector<Enemy_1*> e);
	void Update() override;
	Sprite* player;
//	Sprite* enemy;

	Player* P;
	vector<Sprite*> E;
	vector<Enemy_1*>e;
};

