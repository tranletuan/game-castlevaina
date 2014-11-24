#ifndef CONTRA_H
#define CONTRA_H

#include "Register.h"
#include "Graphic.h"
#include "Timer.h"
#include "Input.h"
#include "Text.h"
#include "CResourcesManager.h"
#include "SceneManager.h"
#include "Audio.h"

class GameContra
{

private:
	CRegister *m_register;
	CGraphic *m_graphic;
	CTimer *m_timer;
	CInput *m_input;		
	CText *m_text;

	CAudio *m_audio;	
	SceneManager *m_sceneManager;

	

public:

	LPD3DXSPRITE m_spriteHandler;
	LPD3DXFONT m_pFont;

	GameContra();
	~GameContra();

	int initGame(HINSTANCE hIstance);
	int runGame();
	int endGame();

	void updateWorld(int time);
	void drawWorld();

};

#endif 