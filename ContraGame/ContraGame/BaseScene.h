#ifndef BASESCENE_H
#define BASESCENE_H

#include "SceneID.h"
#include "CResourcesManager.h"
#include "Input.h"
#include "Sprite.h"
#include "Audio.h"

class BaseScene
{
protected:
	SceneType m_TypeScene;
	CResourcesManager *m_resource;
	int m_timeDuring; // thoi gian cho de next scene
	CInput *m_input;

	bool m_nextScene;
	bool m_backScene;
	CAudio *m_audio;
	CSound *m_music_bg;
	bool m_onSound;


public:
	BaseScene();
	~BaseScene();

	virtual void processInput();
	virtual void init();
	virtual void draw();
	virtual void update(float time);
	virtual void destroy();
	virtual SceneType getSceneID()=0;

	void setTimeDur(int x){ m_timeDuring = x; }
	int getTimeDur(){ return m_timeDuring; }
	void setNextScene(bool x){  m_nextScene = x; }
	bool getNextScene(){ return m_nextScene; }
	void setBackScene(bool x){ m_backScene = x; }
	bool getBackScene(){ return m_backScene; }


};

#endif