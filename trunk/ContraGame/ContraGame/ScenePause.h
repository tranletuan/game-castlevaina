#ifndef SCENEPAUSE_H
#define SCENEPAUSE_H

#include "BaseScene.h"
#include "SceneManager.h"

class SceneManager;
class ScenePause :
	public BaseScene
{
private:
	CSprite *m_sp1P; // 1p
	CSprite *m_spHi; // High score
	CSprite *m_spTitle; // title pause
	CSprite *m_spRest; // rest: mang song
	CSprite *m_spNumber; 
	CSprite *m_spConti; // nut continue
	CSprite *m_spEnd;  // nut end
	CSprite *m_spBadge; // huy hieu
	CSprite *m_spStage;
	CSprite *m_spNameStage;

	MenuItem m_curItem;
	int m_timeCount;
	bool m_checkItem; // da chon menu 


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
	// chon menu
	void clickMenuItem();

	SceneType getSceneID(){ return SCENE_PAUSE; }


};

#endif