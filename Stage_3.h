#pragma once
#include "Stage.h"
#include "Player.h"
#include "Boss.h"
class Stage_3 :
	public Stage
{
public:
	Stage_3();
	void Collide() override;
	void Update() override;
	void Clear() override;

	Player* player;
	Sprite* map;
	Boss* boss;
};

