#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "SceneID.h"
#include <cstdio>
#include "BaseScene.h"
#include "SceneMenu.h"
#include "Input.h"
#include "SceneLoading.h"
#include "ScenePlay.h"

class SceneMenu;
class ScenePlay;
class SceneLoading;
class SceneManager
{

private:
	static SceneManager *m_sceneManager;
	BaseScene *m_curScene;
	SceneType m_typeScene;
	SceneMenu *m_sceneMenu;
	SceneLoading *m_sceneLoad;
	ScenePlay *m_scenePlay;

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

	void createMenuScene();
	void loadMenuScene();
	void destroyMenuScene();

	void createLoadingScene();
	void destroyLoadingScene();

	void createPlayScene();
	void destroyPlayScene();
};

#endif