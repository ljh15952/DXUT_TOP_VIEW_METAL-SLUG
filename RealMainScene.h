#pragma once
#include "Scene.h"
#include "Sprite.h"
class RealMainScene : public Scene
{
public:
	Sprite* bg;
	Sprite* load;

	void Init() override;
	void Update() override;
	void OnExit() override;

	float timer;
	bool isclick;
};

