#pragma once

#include "SDL.h"

#define GET_MOUSE_POS(p) SDL_GetMouseState(&p.x, &p.y)

#define GET_SCREEN_DIMENSIONS() Unknown::getUnknown()->screenSize