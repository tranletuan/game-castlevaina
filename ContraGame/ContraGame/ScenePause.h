#ifndef SCENEPAUSE_H
#define SCENEPAUSE_H

#include "BaseScene.h"
#include "SceneManager.h"

class SceneManager;
class ScenePause :
	public BaseScene
{
private:
	CSprite *m_sp1P;
	CSprite *m_spHi;
	CSprite *m_spName;
	CSprite *m_spNumber;
	CSprite *m_spConti;
	CSprite *m_spEnd;

public:
	ScenePause();
	~ScenePause();

	void processInput();
	void init();
	void draw();
	void update(float time);
	void destroy();

	// ve so diem 
	void drawNumber(string str, float posX, float posY);

	SceneType getSceneID(){ return SCENE_PAUSE; }


};

#endif