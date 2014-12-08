#ifndef SCENELOADING_H
#define SCENELOADING_H

#include "BaseScene.h"
#include "SceneManager.h"

class SceneManager;
class SceneLoading: 
	public BaseScene
{
private:
	CSprite *m_sp1P;
	CSprite *m_spRest;
	CSprite *m_spHi;
	CSprite *m_spStage;
	CSprite *m_spNumber;
	CSprite *m_spNameStage;

	int _highScore;
	

public:
	SceneLoading();
	~SceneLoading();

	void processInput();
	void init();
	void draw();
	void update(float time);
	void destroy();

	// ve so diem cao
	void drawNumber(string str, float posX, float posY);

	SceneType getSceneID(){ return SCENE_LOADING; }


};



#endif