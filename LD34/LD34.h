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

class LD34
{
public:
	static GameMode curMode;
	static Unknown::Map map;
	static Player* player;
	static Unknown::Graphics::Font* font;
};

void onSwitchMode(Unknown::KeyEvent evnt);

#endif