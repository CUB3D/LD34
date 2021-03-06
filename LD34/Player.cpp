#include "stdafx.h"
#include "Player.h"

#include "LD34.h"
#include "CustomEntity.h"
#include "Loader.h"
#include "Utils.h"

Player::Player(Unknown::Sprite* sprite) : Unknown::HealthEntity(sprite, 10), speedT(5), spriteFlipped("res/player/flipped.png")
{
	UK_ADD_MOUSE_LISTENER_INTERNAL(this->onShoot, "PLAYER_SHOOT");

	this->sprite->bounds.size.width = 16;
	this->sprite->bounds.size.height = 16;

	this->spriteNorm = ((Unknown::Graphics::ImageSprite*)sprite)->image;
}

void Player::update()
{
	if (!this->isAlive())
		return;

	if (speedT.isTickComplete())
	{
		if (speed < maxSpeed)
		{
			speed++;
		}
	}


	if (LD34::curMode != GameMode::MODE_MOVE)
	{
		return;
	}

	Unknown::Point<int> mPos;

	GET_MOUSE_POS(mPos);

	if (mPos.x > this->sprite->location.x)
	{
		this->sprite->setAngle(0);
		((Unknown::Graphics::ImageSprite*)this->sprite)->image = 
			spriteNorm;
	}

	if (mPos.x < this->sprite->location.x)
	{
		this->sprite->setAngle(180);
		((Unknown::Graphics::ImageSprite*)this->sprite)->image = &spriteFlipped;
	}

	this->sprite->move(speed, 0);
}

void Player::onShoot(Unknown::MouseEvent evnt)
{
	if (!this->isAlive())
		return;


	if (evnt.mouseButton == Unknown::MouseButton::BUTTON_LEFT)
	{
		if (evnt.buttonState == Unknown::InputState::PRESSED)
		{
			if (LD34::curMode == GameMode::MODE_MOVE)
			{
				//shoot
				Unknown::Sprite* bulletSpr = UK_LOAD_SPRITE("res/bullet/BulletSprite.json");

				bool isLeft = this->sprite->getAngle() == 180;

				Bullet* bullet = new Bullet(bulletSpr, isLeft, false);

				bullet->sprite->location.x = this->sprite->location.x + 16 - bullet->sprite->bounds.size.width;
				bullet->sprite->location.y = this->sprite->location.y + 8;

				UK_REGISTER_ENTITY(bullet);
			}
			else
			{
				if (!placing)
				{
					placing = &LD34::tiles[0];
				}

				Unknown::Point<int> mPos;

				GET_MOUSE_POS(mPos);

				for (int i = 0; i < TILE_COUNT; i++)
				{
					Tile a = LD34::tiles[i + 1];
					a.img->render(i * TILE_WIDTH + 10, 37);

					int butX = i * TILE_WIDTH + 10;
					int butY = 37;

					if (mPos.x > butX && mPos.x < butX + TILE_WIDTH)
					{
						if (mPos.y > butY && mPos.y < butY + TILE_HEIGHT)
						{
							placing = &LD34::tiles[i + 1];
						}
					}
				}

				TilePos* inTile = LD34::isInTile(mPos.x, mPos.y);

				if (inTile)
				{
					//std::cout << inTile->x << " " << inTile->y << std::endl;

					if (LD34::buy(placing->cost))
					{
						LD34::map.setTileID(placing->id, inTile->x, inTile->y);
					}
					else
					{
						std::cout << "Cannot afford" << std::endl;
					}
				}
			}
		}
	}
}

const std::string Player::getEntityID() const
{
	return "PLAYER";
}

void Player::handleCollision(Entity * ent)
{
	if (speed > 1)
	{
		speed--;
	}
	ent->kill();
}


Player::~Player()
{
}
