#pragma once
#include "Entity.h"
#include "Timer.h"

class Bullet : public Unknown::TwoStateEntity
{
public:
	bool isLeft;
	bool enemy;

	Bullet(Unknown::Sprite* bullet, bool isLeft, bool enemy);
	virtual void update() override;
	virtual const std::string getEntityID() const override;
	virtual void handleCollision(Entity* ent) override;
};

class Enemy : public Unknown::TwoStateEntity
{
public:
	Unknown::Timer shoot;
	Enemy(Unknown::Sprite* bullet);
	virtual void update() override;
	virtual const std::string getEntityID() const override;
};

