#include "stdafx.h"
#include "Player.h"

#include "LD34.h"
#include "Bullet.h"
#include "Loader.h"
#include "Utils.h"

Player::Player(Unknown::Sprite* sprite) : Unknown::HealthEntity(sprite, 10)
{
	UK_ADD_MOUSE_LISTENER_INTERNAL(this->onShoot, "PLAYER_SHOOT");
}

void Player::update()
{
	if (LD34::curMode != GameMode::MODE_MOVE)
	{
		return;
	}

	Unknown::Point<int> mPos;

	GET_MOUSE_POS(mPos);

	if (mPos.x > this->sprite->location.x)
	{
		this->sprite->move(1, 0);
	}

	if (mPos.x < this->sprite->location.x)
	{
		this->sprite->move(-1, 0);
	}
}

void Player::onShoot(Unknown::MouseEvent evnt)
{
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

			Bullet* bullet = new Bullet(bulletSpr);

			bullet->sprite->location.x = this->sprite->location.x + 16 - bullet->sprite->bounds.size.width;
			bullet->sprite->location.y = this->sprite->location.y + 8;

			UK_REGISTER_ENTITY(bullet);

		}
	}
}


Player::~Player()
{
}
