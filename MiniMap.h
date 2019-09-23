#pragma once
#include "Sprite.h"
#include "Player.h"
#include "Enemy_1.h"
class MiniMap : public Sprite
{
public:
	MiniMap(Player* p);
	~MiniMap();
	void Update() override;
	Sprite* player;

	Player* P;
};

