#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Camera.h"
#include "Bullet.h"
#include "Player.h"
#include "MiniMap.h"
#include "Enemy_1.h"
class MainScene : public Scene
{
public:
	void Init() override;
	void Update() override;
	void OnExit() override;


	Player* P;
	Sprite* S2;
	MiniMap* Minimap;

	Sprite* feulSp;

	float spawntimer;

	vector<Sprite*> walls;
};

