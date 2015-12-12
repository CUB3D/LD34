// LD34.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Unknown.h"
#include "SDL.h"


void render()
{
	
}

void update()
{

}

int main(int argc, char* argv[])
{
	UK_CREATE_WINDOW();

	UK_RENDER(render);
	UK_UPDATE(update);

	UK_INIT_GAME();

    return 0;
}

