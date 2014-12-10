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
	
	// scene manager	
	m_sceneManager = SceneManager::getInstance();
	m_sceneManager->createMenuScene();
	//SceneManager::getInstance()->createPlayScene();
	//SceneManager::getInstance()->createLoadingScene();

	return 1;

}

int GameContra::runGame()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	DWORD frame_start = GetTickCount();
	DWORD tick_per_fram = 1000 / kFrameRate;

	//Vòng lặp chính quản lý thông điệp
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		DWORD delta_time = now - frame_start;

		if (delta_time >= tick_per_fram)
		{
			updateWorld(delta_time);
			//Vẽ các thành phần trong game;
			drawWorld();
			frame_start = now;
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

void GameContra::updateWorld(int time)
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