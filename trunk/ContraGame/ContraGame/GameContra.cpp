#include "GameContra.h"
 
GameContra::GameContra()
{
	
}

int GameContra::initGame(HINSTANCE hIstance)
{
	
	// register window
	m_register = new CRegister(hIstance);
	if (!m_register->initWindow(hIstance))
	{
		MessageBox(m_register->getHandle(), "Can't Create Windows", "Error", MB_OK);
		return 0;
	}
	// graphics
	m_graphic = new CGraphic();
	if (!m_graphic->initDevice(m_register->getHandle()))
	{
		MessageBox(m_register->getHandle(), "Can't Create Graphic Device", "Error", MB_OK);
		return 0;
	}

	// timer
	m_timer = new CTimer();
	m_timer->setMaxFps(60.0f);

	//input
	m_input = new CInput();
	if (!m_input->initInput(m_register->gethInstance()))
	{
		MessageBox(m_register->getHandle(), "Can't Create input device", "Error", MB_OK);
		return 0;
	}
	if (!m_input->initKeyboard(m_register->getHandle()))
	{
		MessageBox(m_register->getHandle(), "Can't Create Keyboard", "Error", MB_OK);
		return 0;
	}

	// sprite

	if (FAILED(D3DXCreateSprite(m_graphic->getPd3Device(), &m_spriteHandler)))
	{
		MessageBox(m_register->getHandle(), "Can't Create Sprite ", "Error", MB_OK);		
		return 0;
	}
		

	// text
	m_text = new CText(m_pFont, "Arial", m_graphic->getPd3Device(), m_spriteHandler);

	if (!m_text->init())
	{
		MessageBox(m_register->getHandle(), "Can't Create Text", "Error", MB_OK);
		return 0;
	}

	// audio
	m_audio = new CAudio(m_register->getHandle());
	if (m_audio == NULL)
	{
		MessageBox(m_register->getHandle(), "Can't Init Sound ", "Error", MB_OK);
		return 0;
	}

	// resource manager
	CResourcesManager::prepareManager(m_spriteHandler, m_graphic->getPd3Device(), m_register->gethInstance(), 
		m_register->getHandle(), m_input, m_audio);
	CResourcesManager::GetInstance()->m_levelMap = 1;
	CResourcesManager::GetInstance()->m_life = 3;

	// scene manager
	
	m_sceneManager = SceneManager::getInstance();
	//SceneManager::getInstance()->createMenuScene();
	SceneManager::getInstance()->createPlayScene();
	
	return 1;

}

int GameContra::runGame()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	int done = 0;
	while (!done)
	{
		m_timer->startCount();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = 1;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{			
			if (m_timer->getTime() < 1.0f)
			{
				updateWorld(m_timer->getDeltaTime());
				drawWorld();
				m_timer->endCount();
			}
		}

	}
	return (int)msg.wParam;
}

int GameContra::endGame()
{
	if(m_register != NULL)
	{
		delete m_register;
	}
	if (m_graphic != NULL)
	{
		delete m_graphic;
	}

	return 1;
}

void GameContra::updateWorld(float time)
{
	m_input->processKeyBoard();

	m_sceneManager->processInput();
	m_sceneManager->update(time);
}

void GameContra::drawWorld()
{
	m_graphic->beginRender();
	m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	
	// Draw any thing
	//-------------------------

	m_sceneManager->getInstance()->draw();

	//-------------------------
	m_spriteHandler->End();
	m_graphic->endRender();
}

GameContra::~GameContra()
{

}