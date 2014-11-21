#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "BaseScene.h"
#include "MenuID.h"
#include "SceneManager.h"

class SceneManager;
class SceneMenu : 
	public BaseScene
{
private:
	CSprite *m_spBG;
	CSprite *m_spItem1;
	CSprite *m_spItem2;
	CSprite *m_spBadge;

	CSound *m_musicbg;

	D3DXVECTOR2 m_deltaVec;
	bool m_runBG;
	MenuItem m_curItem;
	bool m_checkItem;


public:
	SceneMenu();
	~SceneMenu();
	void processInput();
	void init();
	void draw();
	void update(float time);
	void destroy();
	SceneType getSceneID(){ return SCENE_MENU; }

	D3DXVECTOR2 getDeltaVec(){ return m_deltaVec; }
	void setDeltaVec(D3DXVECTOR2 x){ m_deltaVec = x; }
	void setRunBG(bool x){ m_runBG = x; }
	bool getRunBG(){ return m_runBG; }
	void setMenuItem(MenuItem x){ m_curItem = x; }
	MenuItem getMenuItem(){ return m_curItem; }
	void setCheckItem(bool x){ m_checkItem = x; }
	bool getCheckItem(){ return m_checkItem; }

	void defaulPostionBG();
	void clickMenuItem();
};



#endif