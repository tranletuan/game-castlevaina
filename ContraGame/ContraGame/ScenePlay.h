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
#include "CListItemFly.h"
#include "CRunManManager.h"
#include "SceneManager.h"

#include "CBoss3.h"

enum PlayState
{
	PS_InGame,
	PS_GameOver, // mạng =0 , game over
	PS_Pause,
	PS_WaitNextScene, // Đợi chuyển qua scene 
	PS_NextMap,  // next map
};

class SceneManager;
class ScenePlay:
	public BaseScene
{
private:

	int _countScore; // Biến này sử dụng để thêm 1 mạng
	PlayState m_state;

	Background *m_background;
	CameraHUD *m_cameraHUD;
	CCamera *m_camera;
	QTTree *m_tree;

	CBill* _player1;
	CBill* _player2;

	CPlayerWeapon* _weapon_player1;
	CPlayerWeapon* _weapon_player2;
	CEnemyWeapon* _weapon_enemy;

	vector<CObject*> _grounds;
	vector<CObject*> _enemies;
	vector<CObject*> _items;

	CListItemFly *m_listItemFLy;
	CRunmanManager* _runmans;	
	CObject* _boss;

	CBoss3* boss_test;

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