#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"
#include "Entity.h"
#include "Input.h"

class Player : public Unknown::HealthEntity
{
public:
	Player(Unknown::Sprite* sprite);
	virtual void update() override;
	void onShoot(Unknown::MouseEvent evnt);
	~Player();
};

#endif