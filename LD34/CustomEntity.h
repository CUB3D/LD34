#pragma once
#include "Entity.h"

class Bullet : public Unknown::TwoStateEntity
{
public:
	Bullet(Unknown::Sprite* bullet);
	virtual void update() override;
};

class Enemy : public Unknown::TwoStateEntity
{
public:
	Enemy(Unknown::Sprite* bullet);
	virtual void update() override;
};

