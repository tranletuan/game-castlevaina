#ifndef SCENEPLAY_H
#define SCENEPLAY_H

#include "BaseScene.h"
#include "Background.h"
#include "CameraHUD.h"
#include "Camera.h"
#include "QTTree.h"
#include "CBill.h"
#include "CEnemyWaepon.h"

class Background;
class ScenePlay:
	public BaseScene
{
private:
	Background *m_background;
	CameraHUD *m_cameraHUD;
	CCamera *m_camera;
	QTTree *m_tree;
	CBill *m_bill;
	CPlayerWeapon *m_playerWeapon;
	CEnemyWaepon *m_enemyWeapon;

public:
	ScenePlay();
	~ScenePlay();

	void processInput();
	void init();
	void draw();
	void update(float time);
	void destroy();
	// xu ly va cham cac doi tuong
	SceneType getSceneID(){ return SCENE_PLAY; }
};



#endif 