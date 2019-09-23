#include "DXUT.h"
#include "Trash.h"

Trash::Trash(T_Trash_Type T)
{
	if (T == T_Trash_Type::oil)
	{
		Create(L"Oil.png");
	}
	else if (T == T_Trash_Type::trash)
	{
		Create(L"Trash_Dumy.png");
		_layer = 1;
	}
	t = T;
}

void TrasgManager::Make_Trash()
{
	bool b = true;
	for (int i = 0; i < 30; i++)
	{
		Trash* t = new Trash(T_Trash_Type::oil);

		float sosu = rand() % 10;
		sosu /= 10;
		float sosu2 = rand() % 10;
		sosu2 /= 10;

		t->_scale = { 4 - sosu,4 - sosu2 };
		Trash* t1 = new Trash(T_Trash_Type::trash);
		t1->_scale = { 1.7,1.7 };

		if (b)
		{
			Trashs.push_back(t);
			Trashs.push_back(t1);
		}
		else
		{
			Trashs.push_back(t1);
			Trashs.push_back(t);
		}

		b = !b;
	}

	Set_Trash_Pos();
}

void TrasgManager::Delete_Trash()
{
	for (auto it : Trashs)
		delete it;
	Trashs.clear();
}

void TrasgManager::Set_Trash_Pos()
{
	int num = 0;

	// 가로
	for (int j = 1; j <= 3; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			vector2 v = { 300 + float(i * 1000), (2500 * j) - float(rand() % 300) };
			Trashs[num]->_position = v;
			num++;
		}
	}
	//세로
	for (int j = 1; j <= 3; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			vector2 v = { (2500 * j) - float(rand() % 300) ,300 + float(i * 1000) };
			Trashs[num]->_position = v;
			num++;
		}
	}
}
