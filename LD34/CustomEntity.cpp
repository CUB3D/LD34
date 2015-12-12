#include "stdafx.h"
#include "CustomEntity.h"


Bullet::Bullet(Unknown::Sprite* sprite) : Unknown::TwoStateEntity(sprite)
{
}

void Bullet::update()
{
	this->sprite->move(1, 0);
}

Enemy::Enemy(Unknown::Sprite* sprite) : Unknown::TwoStateEntity(sprite)
{
}

void Enemy::update()
{
	this->sprite->move(-1, 0);
}