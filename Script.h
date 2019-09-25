#pragma once
#include "Sprite.h"
class Script
{
public:
	Script();
	Sprite* nowScript;
	Sprite* nowSpeak;
	Sprite* blackback;

	vector<Sprite*> Scripts;
	vector<Sprite*> Speaks;
	int num;
	void SetNextScript();
};

