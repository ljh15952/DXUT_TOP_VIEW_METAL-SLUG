#include "DXUT.h"
#include "Stage_1_Script.h"

Stage_1_Script::Stage_1_Script()
{
	for (int i = 0; i < 10; i++)
	{
		Sprite* s = new Sprite;
		s->Create(L"Script/s"+to_wstring(i)+L".png");
		s->_visible = true;
		Scripts.push_back(s);
	}
	for (int i = 0; i < 10; i++)
	{
		Sprite* s = new Sprite;
		s->Create(L"Script/speak_1/s" + to_wstring(i) + L".png");
		s->_visible = true;
		Speaks.push_back(s);
	}

	SetNextScript(); //부모의 함수 호출
}

Stage_1_Script::~Stage_1_Script()
{
	for (auto it : Speaks)
		delete it;
	Speaks.clear();
	
	for (auto it : Scripts)
		delete it;
	Scripts.clear();
}
