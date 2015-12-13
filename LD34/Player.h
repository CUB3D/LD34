#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"
#include "Entity.h"
#include "Input.h"
#include "LD34.h"

struct Tile;

class Player : public Unknown::HealthEntity
{
public:
	Unknown::Graphics::Image* spriteNorm;
	Unknown::Graphics::Image spriteFlipped;
	int maxSpeed = 2;
	int speed = 2;
	Unknown::Timer speedT;
	Tile* placing;

	Player(Unknown::Sprite* sprite);
	virtual void update() override;
	void onShoot(Unknown::MouseEvent evnt);
	virtual const std::string getEntityID() const override;
	virtual void handleCollision(Entity* ent) override;
	~Player();
};

#endif