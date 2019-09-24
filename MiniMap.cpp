#include "DXUT.h"
#include "MiniMap.h"

MiniMap::MiniMap(Player * p)
{
	Create(L"stage_1/map.png");
	_pivot = { 1,0 };
	_position = { 1280,0 };
	_scale = { 0.035f,0.035f };
	isUI = true;


	P = p;
	player = new Sprite;
	player->Create(L"a/pistol/Handgun_Walk 1.png");
	player->isUI = true;
	player->_position = { _position.x - (7518 * _scale.x) + (P->_position.x * _scale.x) ,(P->_position.y * _scale.y) };
	player->_scale = { 0.5f,0.5f };

}

MiniMap::~MiniMap()
{
	delete player;
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
			it->mini->_position = { _position.x - (7518 * _scale.x) + (it->_position.x * _scale.x) ,(it->_position.y * _scale.y) };
		}
	}
}
