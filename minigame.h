#pragma once
#include "Stage.h"
#include "Player.h"
#include "ShotEnemy.h"
class minigame :
	public Stage
{
public:
	minigame();
	void Clear() override;
	void Collide() override;
	void Update() override;
private:
	Player* player;
	ShotEnemy* Shotenemy[40];
	Label* Scorelabel;
	Sprite* m;
	Sprite* enerygy;
	int scorenum;
	vector<ShotEnemy*> e;
	float timer = 1;
	vector2 asdas;
	bool istracer;
};

