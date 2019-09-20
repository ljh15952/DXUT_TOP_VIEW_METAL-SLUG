#pragma once
#include "Sprite.h"
#include "Types.h"

// Ÿ�����ؼ� �⸧���� ����������
//������ = ������ ü�±��� 
//�⸧�� �ӵ��� ������
//�浹ó�� ������ = ������
//�⸧ = �Ⱦ������� ������
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


