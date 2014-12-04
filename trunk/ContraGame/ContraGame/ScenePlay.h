#ifndef SCENEPLAY_H
#define SCENEPLAY_H

#include <map>
#include "BaseScene.h"
#include "Background.h"
#include "CameraHUD.h"
#include "Camera.h"
#include "QTTree.h"
#include "CBill.h"
#include "CEnemyWeapon.h"
#include "CSniperStand.h"
#include "CSniperHide.h"
#include "CGroundCanon.h"
#include "CWallTurret.h"
#include "CListNoTree.h"
#include "CBoss1.h"
#include "CGroundEffect.h"

class Background;
class ScenePlay:
	public BaseScene
{
private:
	Background *m_background;
	CameraHUD *m_cameraHUD;
	CCamera *m_camera;
	QTTree *m_tree;

	CBill* _player1;
	CBill* _player2;

	CPlayerWeapon* _weapon_player1;
	CPlayerWeapon* _weapon_player2;
	CEnemyWeapon* _weapon_enemy;

	map<int, CObject*> _grounds;
	vector<CObject*> _enemies;
	map<int, CObject*> _items;

	CListNoTree *m_listNoTree;

public:
	ScenePlay();
	~ScenePlay();

	void processInput();
	void init();
	void draw();
	void update(float time);
	void destroy();

	SceneType getSceneID(){ return SCENE_PLAY; }

	void UpdateFullListObjetcInView();
	void ProcessGroundsWithOneAnother();
	void ProcessEnemiesWithOneAnother();
	void ProcessItemsWithOneAnother();
	void UpdateGlobalVariable();
};



#endif 