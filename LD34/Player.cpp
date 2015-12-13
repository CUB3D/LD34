#include "stdafx.h"
#include "Player.h"

#include "LD34.h"
#include "CustomEntity.h"
#include "Loader.h"
#include "Utils.h"

Player::Player(Unknown::Sprite* sprite) : Unknown::HealthEntity(sprite, 10)
{
	UK_ADD_MOUSE_LISTENER_INTERNAL(this->onShoot, "PLAYER_SHOOT");

	this->sprite->bounds.size.width = 16;
	this->sprite->bounds.size.height = 16;
}

void Player::update()
{
	if (!this->isAlive())
		return;

	if (LD34::curMode != GameMode::MODE_MOVE)
	{
		return;
	}

	Unknown::Point<int> mPos;

	GET_MOUSE_POS(mPos);

	if (mPos.x > this->sprite->location.x)
	{
		this->sprite->setAngle(0);
	}

	if (mPos.x < this->sprite->location.x)
	{
		this->sprite->setAngle(180);
	}

	this->sprite->move(1, 0);
}

void Player::onShoot(Unknown::MouseEvent evnt)
{
	if (!this->isAlive())
		return;

	if (LD34::curMode != GameMode::MODE_MOVE)
	{
		return;
	}

	if (evnt.mouseButton == Unknown::MouseButton::BUTTON_LEFT)
	{
		if (evnt.buttonState == Unknown::InputState::PRESSED)
		{
			//shoot
			Unknown::Sprite* bulletSpr = UK_LOAD_SPRITE("res/bullet/BulletSprite.json");

			bool isLeft = this->sprite->getAngle() == 180;

			Bullet* bullet = new Bullet(bulletSpr, isLeft, false);

			bullet->sprite->location.x = this->sprite->location.x + 16 - bullet->sprite->bounds.size.width;
			bullet->sprite->location.y = this->sprite->location.y + 8;

			UK_REGISTER_ENTITY(bullet);

		}
	}
}

const std::string Player::getEntityID() const
{
	return "PLAYER";
}


Player::~Player()
{
}
