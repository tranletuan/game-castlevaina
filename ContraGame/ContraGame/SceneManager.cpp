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
	//m_typeScene = SCENE_PLAY;	
}

SceneManager::~SceneManager()
{

}

void SceneManager::setScene(BaseScene *x)
{
	m_curScene = x;
	m_typeScene = x->getSceneID();
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
	default:
		break;
	}
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

void SceneManager::createMenuScene()
{
	CResourcesManager::GetInstance()->loadMenuResource();
	CResourcesManager::GetInstance()->loadLoadingResource();
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

void SceneManager::createLoadingScene()
{
	CResourcesManager::GetInstance()->loadPlayResource();
	m_sceneLoad = new SceneLoading();
	SceneManager::getInstance()->setScene(m_sceneLoad);
}

void SceneManager::destroyLoadingScene()
{

}

void SceneManager::createPlayScene()
{
	CResourcesManager::GetInstance()->loadPlayResource();
	m_scenePlay = new ScenePlay();
	SceneManager::getInstance()->setScene(m_scenePlay);
}

void SceneManager::destroyPlayScene()
{

}