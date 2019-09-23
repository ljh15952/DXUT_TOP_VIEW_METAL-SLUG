#pragma once
#include "Stage.h"
#include "Camera.h"
#include "Bullet.h"
#include "Player.h"
#include "MiniMap.h"
#include "Enemy_1.h"
#include "UI.h"
#include"Trash.h"
#include "GM.h"
class Stage_1 :
	public Stage
{
public:
	Stage_1();
	~Stage_1();
	void Collide() override;
	void Update() override;
private:
	Player* P;
	Sprite* S2;
	MiniMap* Minimap;

	Sprite* feulSp;

	float spawntimer;

	vector<Sprite*> kick;

	vector<Sprite*> walls;
};

