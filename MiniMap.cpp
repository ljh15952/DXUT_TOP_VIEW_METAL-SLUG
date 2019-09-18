#include "DXUT.h"
#include "MiniMap.h"

//벡터써서 만들자~~
MiniMap::MiniMap(Player * p,Enemy_1 * e)
{
	Create(L"asd.png");
	_pivot = { 1,0 };
	_position = { 1280,0 };
	_scale = { 0.03f,0.03f };
	isUI = true;


	P = p;
	E = e;

	player = new Sprite;
	player->Create(L"a/pistol/Handgun_Walk 1.png");
	player->isUI = true;
	cout << _position.x - (9850 * 0.03f) << endl;
	player->_position = { _position.x - (9850 * 0.03f) + (P->_position.x * 0.03f) ,(P->_position.y * 0.03f) };
	player->_scale = { 0.5f,0.5f };


	enemy = new Sprite;
	enemy->Create(L"soldier1_gun.png");
	enemy->isUI = true;
	cout << _position.x - (9850 * 0.03f) << endl;
	enemy->_position = { _position.x - (9850 * 0.03f) + (E->_position.x*0.03f) ,(E->_position.y * 0.03f) };
	enemy->_scale = { 0.5f,0.5f };
}

void MiniMap::Update()
{
	if (P->v.x >= -1 && !P->iscol)
	{
		player->_rotation = P->_rotation;
		player->_position += P->v * 0.03f * P->Speed;
	}

	enemy->_rotation = E->_rotation;
	//enemy->_position += E->Speed * E->v * 0.03f;
	enemy->_position = { _position.x - (9850 * 0.03f) + (E->_position.x * 0.03f) ,(E->_position.y * 0.03f) };

}
