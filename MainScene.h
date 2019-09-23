#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Stage.h"
#include "Stage_1.h"
#include "Stage_2.h"
#include "Stage_3.h"

class MainScene : public Scene
{
public:
	void Init() override;
	void Update() override;
	void OnExit() override;


	Stage* stage;

};

