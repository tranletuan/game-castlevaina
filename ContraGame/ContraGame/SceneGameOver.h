#ifndef SCENEOVER_H
#define SCENEOVER_H

#include "BaseScene.h"
#include "SceneManager.h"

class SceneManager;
class SceneGameOver :
	public BaseScene
{
private:
	CSprite *m_sp1P; // 1p
	CSprite *m_spHi; // High score
	CSprite *m_spTitle; // title pause	
	CSprite *m_spNumber;
	CSprite *m_spConti; // nut continue
	CSprite *m_spEnd;  // nut end
	CSprite *m_spBadge; // huy hieu


	MenuItem m_curItem;
	int m_timeCount;
	bool m_checkItem; // da chon menu 

public:
	SceneGameOver();
	~SceneGameOver();

	void processInput();
	void init();
	void draw();
	void update(float time);
	void destroy();

	// ve so diem 
	void drawNumber(string str, float posX, float posY);
	void clickMenuItem();
	SceneType getSceneID(){ return SCENE_GAMEOVER; }


};

#endif