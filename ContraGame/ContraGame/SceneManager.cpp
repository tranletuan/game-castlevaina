#include "SceneManager.h"

SceneManager *SceneManager::m_sceneManager = NULL;
SceneManager *SceneManager::getInstance()
{
	if (m_sceneManager == NULL)
	{
		m_sceneManager = new SceneManager();
	}
	return m_sceneManager;
}



SceneManager::SceneManager()
{
	m_typeScene = SCENE_MENU;	
}

SceneManager::~SceneManager()
{

}

void SceneManager::setScene(BaseScene *x)
{
	m_curScene = x;
	m_typeScene = x->getSceneID();
	m_curScene->setNextScene(false);
}

void SceneManager::setScene(SceneType x)
{
	switch (x)
	{
	case SCENE_MENU:
		setScene(m_sceneMenu);
		break;
	case SCENE_LOADING:
		setScene(m_sceneLoad);
		break;
	case SCENE_PLAY:
		setScene(m_scenePlay);
		break;
	case SCENE_PAUSE:
		setScene(m_scenePause);
		break;
	case SCENE_GAMEOVER:
		setScene(m_sceneOver);
		break;
	case SCENE_WIN:
		setScene(m_sceneWin);
		break;
	default:
		break;
	}
	m_curScene->setNextScene(false);
}

void SceneManager::draw()
{
	m_curScene->draw();
}

void SceneManager::update(float time)
{
	m_curScene->update(time);
	
}

void SceneManager::processInput()
{
	m_curScene->processInput();
}

// Menu
void SceneManager::createMenuScene()
{
	CResourcesManager::GetInstance()->loadMenuResource();
	CResourcesManager::GetInstance()->loadLoadingResource();
	CResourcesManager::GetInstance()->loadPauseResource();
	CResourcesManager::GetInstance()->loadOverResource();
	CResourcesManager::GetInstance()->loadWinResource();
	CResourcesManager::GetInstance()->loadPlayResource();
	m_sceneMenu = new SceneMenu();
	SceneManager::getInstance()->setScene(m_sceneMenu);
}

void SceneManager::loadMenuScene()
{
	m_sceneMenu->setTimeDur(20);	
	SceneManager::getInstance()->setScene(m_sceneMenu);
}

void SceneManager::destroyMenuScene()
{

}

// Loading
void SceneManager::createLoadingScene()
{
	CResourcesManager::GetInstance()->readHighScoreOfMap();
	m_sceneLoad = new SceneLoading();
	SceneManager::getInstance()->setScene(m_sceneLoad);
}



void SceneManager::loadLoadingScene()
{
	SceneManager::getInstance()->setScene(m_sceneLoad);
}

void SceneManager::destroyLoadingScene()
{

}

// Play
void SceneManager::createPlayScene()
{
	CResourcesManager::GetInstance()->loadAllInMap();
	m_scenePlay = new ScenePlay();	
	SceneManager::getInstance()->setScene(m_scenePlay);
}

void SceneManager::loadPlayScene()
{	
	SceneManager::getInstance()->setScene(m_scenePlay);
}

void SceneManager::destroyPlayScene()
{

}

// Pause
void SceneManager::createPauseScene()
{	
	m_scenePause = new ScenePause();
	SceneManager::getInstance()->setScene(m_scenePause);

}

void SceneManager::loadPauseScene()
{
	SceneManager::getInstance()->setScene(m_scenePause);
}

void SceneManager::destroyPauseScene()
{

}

// GameOver
void SceneManager::createOverScene()
{
	
	m_sceneOver = new SceneGameOver();
	SceneManager::getInstance()->setScene(m_sceneOver);
}

void SceneManager::loadOverScene()
{	
	SceneManager::getInstance()->setScene(m_sceneOver);
}

void SceneManager::destroyOverScene()
{

}

// Win Game

void SceneManager::createWinScene()
{	
	m_sceneWin = new SceneWin();
	SceneManager::getInstance()->setScene(m_sceneWin);

}

void SceneManager::loadWinScene()
{
	SceneManager::getInstance()->setScene(m_sceneWin);
}

void SceneManager::destroyWinScene()
{

}