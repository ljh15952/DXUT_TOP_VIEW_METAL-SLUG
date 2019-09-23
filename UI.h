#pragma once
#include "Types.h"
#include "Sprite.h"
class UI : public Singleton<UI>
{
public:
	void UI_Init();
	
	Sprite* weapons[3];
	Sprite* mission;
	Sprite* missionText;
	Sprite* Hp[3];
	Sprite* profile[2];
	Sprite* blackback;
	Sprite* name[2];
	Sprite* script[2];

	void SetHpUI(int Hp);
	void SetmissinUI();
	void SetmissionTextUI();
	void SetprofileUI();
	void SetNextScriptUI();

	bool isScript;

	int scriptnum;
	int clicknum;

	void DeleteUI();
};

