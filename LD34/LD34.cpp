// LD34.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Unknown.h"
#include "SDL.h"
#include "Image.h"
#include "Map.h"

#include <iostream>

#define TILE_SIZE 16

Unknown::Map map(10, 25);

struct Tile
{
	int id;
	Unknown::Graphics::Image* img;

	void render(int x, int y)
	{
		img->render(x * TILE_SIZE + 256 - 16 * map.mapSize->width / 2, (32 - y) * TILE_SIZE);
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

	for (int x = 0; x < map.mapSize->width; x++)
	{
		for (int y = 0; y < map.mapSize->height; y++)
		{
			map.setTileID(0, x, y);
		}
	}
}

void render()
{
	for (int x = 0; x < map.mapSize->width; x++)
	{
		for (int y = map.mapSize->height - 1; y > 0; y--)
		{
			int tileID = map.getTileID(x, y);

			tiles[tileID].render(x, y);
		}
	}
}

void update()
{

}

int main(int argc, char* argv[])
{
	init();

	UK_CREATE_WINDOW();

	UK_RENDER(render);
	UK_UPDATE(update);

	UK_INIT_GAME();

    return 0;
}

