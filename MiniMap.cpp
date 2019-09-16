#include "DXUT.h"
#include "MiniMap.h"

MiniMap::MiniMap(Player * p)
{
	Create(L"asd.png");
	_pivot = { 1,0 };
	_position = { 1280,0 };
	_scale = { 0.03f,0.03f };
	isUI = true;


	P = p;

	player = new Sprite;
	player->Create(L"a/Handgun_Walk 1.png");
	player->isUI = true;
	cout << _position.x - (9000 * 0.03f) << endl;
	player->_position = { _position.x - (9000 * 0.03f) , _position.y + (9000 * 0.03f) };
	player->_scale = { 0.5f,0.5f };

}

void MiniMap::Update()
{
	if (P->v.x >= -1)
	{
		player->_rotation = P->_rotation;
		player->_position += P->v * 0.03f * P->Speed;
	}
}
