// LD34.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LD34.h"
#include "Timer.h"
#include "Utils.h"
#include <sstream>

GameMode LD34::curMode = MODE_MOVE;

Unknown::Map LD34::map(6, 25);

Player* LD34::player;

Unknown::Graphics::Font* LD34::font;

Unknown::Timer enemySpawn(4);

struct Tile
{
	int id;
	Unknown::Graphics::Image* img;

	void render(int x, int y)
	{
		img->render(x * TILE_WIDTH + 64, (32 - y) * TILE_HEIGHT);
	}
};


Tile tiles[1];

void init()
{
	Tile tile;

	tile.id = 0;
	tile.img = new Unknown::Graphics::Image("res/tiles/Tile1.png");

	tiles[0] = tile;

	// empty the map

	for (int x = 0; x < LD34::map.mapSize->width; x++)
	{
		for (int y = 0; y < LD34::map.mapSize->height; y++)
		{
			LD34::map.setTileID(0, x, y);
		}
	}


	LD34::player = new Player(UK_LOAD_SPRITE("res/player/Player.json"));

	LD34::font = new Unknown::Graphics::Font(Unknown::Loader::loadImage("res/Font.png"), "abcdefghijklmnopqrstuvwxyz.,:!1234567890", 16);

	UK_ADD_KEY_LISTENER_EXTERNAL(onSwitchMode, "SWITCH_MODE");
}

void onSwitchMode(Unknown::KeyEvent evnt)
{
	if (evnt.SDLCode == SDLK_SPACE)
	{
		if (evnt.keyState == Unknown::InputState::PRESSED)
		{
			LD34::curMode = (GameMode) ((LD34::curMode + 1) % 2);
		}
	}
}

void render()
{
	UK_DRAW_RECT(0, 0, 512, 35, UK_COLOUR_RGB(200, 200, 200));

	for (int x = 0; x < LD34::map.mapSize->width; x++)
	{
		for (int y = LD34::map.mapSize->height - 1; y > 0; y--)
		{
			int tileID = LD34::map.getTileID(x, y);

			tiles[tileID].render(x, y);
		}
	}

	LD34::font->drawString(LD34::curMode == GameMode::MODE_MOVE ? "mode: move" : "mode: build", 10, 0);

	std::stringstream str;

	str << LD34::player->getHealth();

	LD34::font->drawString("lives: " + str.str(), 10, 16 + 2);

	LD34::player->render();
}

void update()
{
	LD34::player->update();


	if (enemySpawn.isTickComplete())
	{
		spawnEnemy();
	}

	for (auto a : Unknown::entitys)
	{
		if (a->getEntityID() == "BULLET")
		{
			a->sprite->bounds.size.width = 4;
			a->sprite->bounds.size.height = 2;
		}
		else
		{
			a->sprite->bounds.size.width = 16;
			a->sprite->bounds.size.height = 16;
		}
	}
}

void spawnEnemy()
{
	Unknown::Sprite* enemySpr = UK_LOAD_SPRITE("res/enemy/Enemy.json");

	Enemy* enemy = new Enemy(enemySpr);

	const Unknown::Dimension<int>* screenSize = GET_SCREEN_DIMENSIONS();

	enemy->sprite->location.x = screenSize->width - 20;
	enemy->sprite->location.y = screenSize->height - 16;

	UK_REGISTER_ENTITY(enemy);
}

int main(int argc, char* argv[])
{
	UK_CREATE_WINDOW();

	init();

	UK_RENDER(render);
	UK_UPDATE(update);

	UK_INIT_GAME();

    return 0;
}

