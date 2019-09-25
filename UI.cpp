#include "DXUT.h"
#include "UI.h"
#include "GM.h"
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
		Hp[i]->_scale = { 0.6f,0.6f };
		Hp[i]->_position = { 25 + float(i * 35),130 };
	}



	for (int i = 0; i < 2; i++)
	{
		profile[i] = new Sprite;
		profile[i]->Create(L"UI/P" + to_wstring(i) + L".png");
		profile[i]->isUI = true;
		profile[i]->_position = { 150 + float(i * 70),200 };
	}

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

	
	if (GM::GetInstance()->stagenum == 2)
	{
		missionText->_visible = false;
		mission->_visible = false;
	}

	isScript = true;
	scriptnum = 0;
	clicknum = 0;
}

void UI::SetHpUI(int hp)
{
	Hp[hp]->_visible = false;
}

void UI::SetmissinUI()
{
}

void UI::SetmissionTextUI()
{
}

void UI::SetprofileUI()
{
}



void UI::DeleteUI()
{
	for (int i = 0; i < 3; i++)
	{
		delete weapons[i];
		delete Hp[i];
	}

	for (int i = 0; i < 2; i++)
	{
		delete profile[i];
	}

	delete mission;
	delete missionText;
}
     