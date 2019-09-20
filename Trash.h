#pragma once
#include "Sprite.h"
#include "Types.h"

// 타입정해서 기름인지 쓰래기인지
//쓰래기 = 맞으면 체력깎임 
//기름은 속도가 느려짐
//충돌처리 쓰래기 = 없어짐
//기름 = 안없어지고 느려짐
class Trash : public Sprite
{
public:
	Trash(T_Trash_Type T);
	T_Trash_Type t;
	int Hp;
};

class TrasgManager : public Singleton<TrasgManager>
{
public:
	void Make_Trash();
	void Delete_Trash();
	vector<Trash*> Trashs;
};


