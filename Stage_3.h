#pragma once
#include "Stage.h"
class Stage_3 :
	public Stage
{
public:
	Stage_3();
	~Stage_3();
	void Collide() override;
	void Update() override;
	void Clear() override;

};

