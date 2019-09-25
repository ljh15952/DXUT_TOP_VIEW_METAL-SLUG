#include "DXUT.h"
#include "Script.h"

Script::Script()
{
	cout << "sexsex" << endl;
	num = -1;

	nowScript = new Sprite;
	nowScript->Create(L"");
	nowScript->_position = { 100,100 };
	nowScript->isUI = true;

	nowSpeak = new Sprite;
	nowSpeak->Create(L"");
	nowSpeak->_position = { 200,100 };
	nowSpeak->isUI = true;

	blackback = new Sprite;
	blackback->Create(L"UI/Sub_bg.png");
	blackback->_pivot = { 0,1 };
	blackback->isUI = true;
	blackback->_visible = false;
	blackback->_position = { 0,720 };
}

void Script::SetNextScript()
{
	num++;
	nowScript->texture = Scripts[num]->texture;
	nowSpeak->texture = Speaks[num]->texture;
}
