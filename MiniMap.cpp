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
	player->Create(L"a/pistol/Handgun_Walk 1.png");
	player->isUI = true;
	player->_position = { _position.x - (9850 * 0.03f) + (P->_position.x * 0.03f) ,(P->_position.y * 0.03f) };
	player->_scale = { 0.5f,0.5f };

}

void MiniMap::Update()
{
	if (!GM::GetInstance()->isgamestart)
		return;
	if (P->v.x >= -1 && !P->iscol)
	{
		player->_rotation = P->_rotation;
		player->_position += P->v * 0.03f * P->Speed;
	}
	
	for (auto it : EnemyManager::GetInstance()->_enemys)
	{
		if (it->_visible)
		{
			it->mini->_rotation = it->_rotation;
			it->mini->_position = { _position.x - (9850 * 0.03f) + (it->_position.x * 0.03f) ,(it->_position.y * 0.03f) };
		}
	}
}
