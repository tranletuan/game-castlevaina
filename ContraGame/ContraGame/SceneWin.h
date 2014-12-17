#ifndef SCENEWIN_H
#define SCENEWIN_H

#include "BaseScene.h"
#include "SceneManager.h"

class SceneManager;
class SceneWin
	:public BaseScene
{
private:
	int m_count;// so lan nhan nut enter
	D3DXVECTOR2 m_pos;

	CSprite* m_spCongru;
	CSprite* m_spVictory;
	CSprite* m_spLead;
	CSprite* m_spThay;
	CSprite* m_spPro;
	CSprite* m_spTien;
	CSprite* m_spTuan;
	CSprite* m_spCopy;

public:
	SceneWin();
	~SceneWin();	

	void processInput();
	void init();
	void draw();
	void update(float time);
	void destroy();

	SceneType getSceneID(){ return SCENE_WIN; }

	void drawBackground(D3DXVECTOR2 pos);
};


#endif