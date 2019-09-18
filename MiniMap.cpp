#include "DXUT.h"
#include "MiniMap.h"

//벡터써서 만들자~~
MiniMap::MiniMap(Player * p,vector<Enemy_1 *> e)
{
	Create(L"asd.png");
	_pivot = { 1,0 };
	_position = { 1280,0 };
	_scale = { 0.03f,0.03f };
	isUI = true;


	P = p;
	this->e = e;
	player = new Sprite;
	player->Create(L"a/pistol/Handgun_Walk 1.png");
	player->isUI = true;
	cout << _position.x - (9850 * 0.03f) << endl;
	player->_position = { _position.x - (9850 * 0.03f) + (P->_position.x * 0.03f) ,(P->_position.y * 0.03f) };
	player->_scale = { 0.5f,0.5f };

	for (auto it : e)
	{
		Sprite * enemy = new Sprite;
		enemy->Create(L"E/Walk/w1.png");
		enemy->isUI = true;
		cout << _position.x - (9850 * 0.03f) << endl;
		enemy->_position = { _position.x - (9850 * 0.03f) + (it->_position.x * 0.03f) ,(it->_position.y * 0.03f) };
		enemy->_scale = { 0.5f,0.5f };
		E.push_back(enemy);
	}
}

void MiniMap::Update()
{
	if (P->v.x >= -1 && !P->iscol)
	{
		player->_rotation = P->_rotation;
		player->_position += P->v * 0.03f * P->Speed;
	}
	cout << E.size() << endl;
	for (int i=0;i<E.size();i++)
	{
		E[i]->_rotation = e[i]->_rotation;
		//enemy->_position += E->Speed * E->v * 0.03f;
		E[i]->_position = { _position.x - (9850 * 0.03f) + (e[i]->_position.x * 0.03f) ,(e[i]->_position.y * 0.03f) };
	}

}
