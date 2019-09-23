#pragma once
#include "Stage.h"
class Stage_2 : public Stage
{
public:
	Stage_2();
	~Stage_2();
	void Collide() override;
	void Update() override;
};

