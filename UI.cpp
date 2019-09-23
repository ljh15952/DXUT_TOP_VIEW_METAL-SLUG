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


	blackback = new Sprite;
	blackback->Create(L"UI/Sub_bg.png");
	blackback->_pivot = { 0,1 };
	blackback->isUI = true;
	blackback->_position = { 0,720 };

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

		script[i] = new Sprite;
		script[i]->Create(L"UI/script" + to_wstring(i) + L".png");
		script[i]->_position = { 300,600 };
		script[i]->isUI = true;
	}
	script[1]->_visible = false;
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

void UI::SetNextScriptUI()
{
	clicknum++;
	if (clicknum == 2)
	{
		GM::GetInstance()->isgamestart = true;
		isScript = false;
		
		for (int i = 0; i < 2; i++)
		{
			script[i]->_visible = false;
			name[i]->_visible = false;
		}
		blackback->_visible = false;
		return;
	}

	script[scriptnum]->_visible = false;
	scriptnum++;
	script[scriptnum]->_visible = true;

	if (scriptnum % 2 == 0)
	{
		name[0]->_visible = true;
		name[1]->_visible = false;
	}
	else
	{
		name[0]->_visible = false;
		name[1]->_visible = true;
	}
	
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
		delete name[i];
		delete script[i];
	}

	delete mission;
	delete missionText;
	delete blackback;
}
     