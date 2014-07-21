#include <Windows.h>
#include "global.h"
#include "game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	kHInstance = hInstance;

	Game *game = new Game(nCmdShow);
	
	game->GameInit();
	game->GameRun();
	game->GameEnd();

	return 0;
}