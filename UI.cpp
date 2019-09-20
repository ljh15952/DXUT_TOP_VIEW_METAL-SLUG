#include "DXUT.h"
#include "UI.h"

void UI::UI_Init()
{
	for (int i = 0; i < 3; i++)
	{
		weapons[i] = new Sprite;
		weapons[i]->Create(L"UI/w" + to_wstring(i) + L".png");
		weapons[i]->isUI = true;
		weapons[i]->_position = { 150 + float(i*70),100 };

		Hp[i] = new Sprite;
		Hp[i]->Create(L"UI/Heart.png");
		Hp[i]->isUI = true;
		Hp[i]->_position = { 150 + float(i * 70),30 };
	}

	for (int i = 0; i < 2; i++)
	{
		profile[i] = new Sprite;
		profile[i]->Create(L"UI/P" + to_wstring(i) + L".png");
		profile[i]->isUI = true;
		profile[i]->_position = { 150 + float(i * 70),200 };

		name[i] = new Sprite;
		name[i]->Create(L"UI/N" + to_wstring(i) + L".png");
		name[i]->isUI = true;
		name[i]->_position = { 100,535 };
	}
	name[1]->_visible = false;

	profile[0]->_position = { 60,60 };
	profile[1]->_visible = false;

	mission = new Sprite;
	mission->Create(L"UI/Mission.png");
	mission->isUI = true;
	mission->_position = { 640,30 };

	missionText = new Sprite;
	missionText->Create(L"UI/Mission_text.png");
	missionText->isUI = true;
	missionText->_position = { 640,80 };

	blackback = new Sprite;
	blackback->Create(L"UI/Sub_bg.png");
	blackback->_pivot = { 0,1 };
	blackback->isUI = true;
	blackback->_position = { 0,720 };


	
	//script;
}
