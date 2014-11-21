#include "GameContra.h"
#include <ctime>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL));
	GameContra *m_game;
	m_game = new GameContra();
	if (!m_game->initGame(hInstance))
	{
		return 0;
	}

	m_game->runGame();
	m_game->endGame();

	return 1;	
}
