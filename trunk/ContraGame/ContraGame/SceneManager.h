#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "SceneID.h"
#include <cstdio>
#include "BaseScene.h"
#include "SceneMenu.h"
#include "Input.h"
#include "SceneLoading.h"
#include "ScenePlay.h"
#include "ScenePause.h"
#include "SceneGameOver.h"

class SceneMenu;
class ScenePlay;
class SceneLoading;
class SceneGameOver;
class ScenePause;

class SceneManager
{

private:
	static SceneManager *m_sceneManager;
	BaseScene *m_curScene;
	SceneType m_typeScene;
	SceneMenu *m_sceneMenu;
	SceneLoading *m_sceneLoad;
	ScenePlay *m_scenePlay;
	SceneGameOver *m_sceneOver;
	ScenePause *m_scenePause;

	SceneManager();

public:
	

	~SceneManager();
	static SceneManager *getInstance();

	void draw();
	void update(float time);
	void processInput();
	
	

	void setScene(BaseScene *x);
	void setScene(SceneType x);
	BaseScene *getCurScene(){ return m_curScene; };
	SceneType getTypeScene() { return m_typeScene; };

	// Menu
	void createMenuScene();
	void loadMenuScene();
	void destroyMenuScene();
	// Loading
	void createLoadingScene();
	void loadLoadingScene();
	void destroyLoadingScene();
	// Play
	void createPlayScene();
	void loadPlayScene();
	void destroyPlayScene();
	// Pause
	void createPauseScene();
	void loadPauseScene();
	void destroyPauseScene();
	// GameOver
	void createOverScene();
	void loadOverScene();
	void destroyOverScene();

};

#endif