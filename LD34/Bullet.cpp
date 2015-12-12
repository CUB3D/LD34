#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(Unknown::Sprite* sprite) : Unknown::TwoStateEntity(sprite)
{
}

void Bullet::update()
{
	this->sprite->move(1, 0);
}


Bullet::~Bullet()
{
}
