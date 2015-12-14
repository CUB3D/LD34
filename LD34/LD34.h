#ifndef LD34_H
#define LD34_H

#include "Unknown.h"
#include "SDL.h"
#include "Image.h"
#include "Map.h"
#include "UI2D.h"
#include "Sprite.h"
#include "Loader.h"
#include "Font.h"

#include "Player.h"
#include "CustomEntity.h"

#include <iostream>

#define TILE_WIDTH 64
#define TILE_HEIGHT 16

enum GameMode
{
	MODE_BUILD,
	MODE_MOVE
};

struct Tile
{
	int id;
	int cost;
	Unknown::Graphics::Image* img;

	void render(int x, int y)
	{
		img->render(x * TILE_WIDTH + 64, (32 - y) * TILE_HEIGHT);
	}
};

struct TilePos
{
	int x, y;
	Tile tile;
};

#define TILE_COUNT 2

class Player;

class LD34
{
public:
	static GameMode curMode;
	static Unknown::Map map;
	static Player* player;
	static Unknown::Graphics::Font* font;
	static Tile tiles[];
	static int money;

	static TilePos* isInTile(int x_, int y_)
	{
		for (int x = 0; x < LD34::map.mapSize->width; x++)
		{
			for (int y = 0; y < LD34::map.mapSize->height; y++)
			{
				int tileX = x * TILE_WIDTH + 64;
				int tileY = (32 - y) * TILE_HEIGHT;

				//std::cout << tileX << "    " << x_ << std::endl;

				if (x_ >= tileX && x_ < tileX + TILE_WIDTH)
				{
					if (y_ >= tileY && y_ < tileY + TILE_HEIGHT)
					{
						TilePos* t = new TilePos;

						t->tile = tiles[map.getTileID(x, y)];
						t->x = x;
						t->y = y;
						return t;
					}
				}
			}
		}

		return NULL;
	}

	static bool buy(int cost)
	{
		if (LD34::money >= cost)
		{
			LD34::money -= cost;
			return true;
		}
		else
		{
			return false;
		}
	}
};

void onSwitchMode(Unknown::KeyEvent evnt);
void spawnEnemy();

#endif