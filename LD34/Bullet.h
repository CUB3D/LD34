#pragma once
#include "Entity.h"

class Bullet : public Unknown::TwoStateEntity
{
public:
	Bullet(Unknown::Sprite* bullet);
	virtual void update() override;
	~Bullet();
};

