#include "stdafx.h"
#include "CustomEntity.h"

#include "Player.h"
#include "LD34.h"
#include "Physics.h"
#include "Utils.h"


Bullet::Bullet(Unknown::Sprite* sprite, bool isLeft, bool enemy) : Unknown::TwoStateEntity(sprite), isLeft(isLeft), enemy(enemy)
{
	if (isLeft)
	{
		this->sprite->setAngle(180);
	}
}

#define BULLET_SPEED 20

void Bullet::update()
{
	if (!this->isAlive())
		return;

	this->sprite->move(20, 0);

	const Unknown::Dimension<int>* size = GET_SCREEN_DIMENSIONS();

	if (this->sprite->location.x < -this->sprite->bounds.size.width || this->sprite->location.x > size->width + this->sprite->bounds.size.width)
	{
		this -> kill();
	}

	if (enemy)
	{
		// check for collision
		std::cout << LD34::player->sprite->bounds.size.width;

		if (Unknown::isAABBIntersecting(LD34::player->sprite->bounds, this->sprite->bounds))
		{
			handleCollision(LD34::player);
		}
	}
	else
	{
		for (auto a : Unknown::entitys)
		{
			if (a->getEntityID() == "ENEMY" && a->isAlive())
			{
				if (Unknown::isAABBIntersecting(a->sprite->bounds, this->sprite->bounds))
				{
					handleCollision(a);
				}
			}
		}
	}
}

const std::string Bullet::getEntityID() const
{
	return "BULLET_F";
}

void Bullet::handleCollision(Entity * ent)
{
	ent->damage(1);
	this->kill();
}

Enemy::Enemy(Unknown::Sprite* sprite) : Unknown::TwoStateEntity(sprite), shoot(3)
{
}

void Enemy::update()
{
	if (!isAlive())
	{
		return;
	}

	if (shoot.isTickComplete())
	{
		//shoot
		Unknown::Sprite* bulletSpr = UK_LOAD_SPRITE("res/bullet/BulletSprite.json");

		Bullet* bullet = new Bullet(bulletSpr, true, true);

		bullet->sprite->location.x = this->sprite->location.x + 16 - bullet->sprite->bounds.size.width;
		bullet->sprite->location.y = this->sprite->location.y + 8;

		UK_REGISTER_ENTITY(bullet);
	}

	this->sprite->move(-1, 0);

	if (this->sprite->location.x <= -this->sprite->bounds.size.width) // if the enemy is off the screen
	{
		LD34::player->damage(1);
		this->kill();
	}
}

const std::string Enemy::getEntityID() const
{
	return "ENEMY";
}
