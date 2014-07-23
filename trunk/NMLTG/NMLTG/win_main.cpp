#include <Windows.h>
#include "global.h"
#include "world_test.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	kHInstance = hInstance;

	WorldTest *game = new WorldTest(nCmdShow);
	
	game->GameInit();
	game->GameRun();
	game->GameEnd();

	return 0;
}