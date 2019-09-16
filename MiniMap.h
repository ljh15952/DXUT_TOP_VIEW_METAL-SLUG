#pragma once
#include "Sprite.h"
#include "Player.h"

class MiniMap : public Sprite
{
public:
	MiniMap(Player* p);
	void Update() override;
	Sprite* player;
	Player* P;
};

