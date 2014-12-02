#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <cstdio>
#include <d3dx9.h>
#include <d3d9.h>
#include "Input.h"
#include "Sprite.h"
#include "Texture.h"
#include "CResourcesPath.h"
#include "Audio.h"
#include "Camera.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "QTNode.h"
#include "CObject.h"

using namespace std;

class QTNode;
class CObject;
class CCamera;
class CResourcesManager
{

private:

	static CResourcesManager *m_resource ;
	CResourcesManager();

public:

	// var
	CInput *m_input;	
	CAudio *m_audio;
	CCamera *_camera;
	D3DXVECTOR2 m_posBill;

	int m_levelMap;
	int m_life;	
	int m_heightMap;
	int m_widthMap;
	vector<CObject*> listObinView;
	vector<CObject*> listObNoTree; // list ob khong nam trong quad tree

	/*------    HUD Camera     -----*/
	CTexture *HUD_badge;

	/*--- Menu Resource ----*/
	CTexture *menu_bg;
	CTexture *menu_item1;
	CTexture *menu_item2;
	CTexture *menu_badge;

	CSound *music_menu_bg;

	/*--- Loading Resource ----*/
	CTexture *load_1p;
	CTexture *load_rest;
	CTexture *load_hi;
	CTexture *load_stage;
	CTexture *load_number;
	CTexture *load_nameStage;

	/*--- Play Resource ----*/
	
	// background
	CTexture *background_1;
	CTexture *background_2;

	/* ------ Object	 ------- */

	//Contra 1
	CTexture* _bill_stand;
	CTexture* _bill_jump;
	CTexture* _bill_die;
	CTexture* _bill_move;
	CTexture* _bill_in_water;

	//Bullet 
	CTexture* _bullet_n;
	CTexture* _bullet_s;
	CTexture* _bullet_l;
	CTexture* _bullet_f;
	CTexture* _bullet_m;
	CTexture* _bullet_ne;
	CTexture* _bullet_b;

	//Ground
	CTexture* _ground_grass;
	CTexture* _ground_water;
	CTexture* _ground_effect1;
	CTexture* _ground_auto_destroy_bridge;

	//Effect
	CTexture* _effect_destroy;
	CTexture* _effect_shoot;
	CTexture* _effect_die;

	//Enemy
	CTexture* _enemy_sniper_stand;
	CTexture* _enemy_sniper_hide;
	CTexture* _enemy_wall_turret;
	CTexture* _enemy_ground_canon;

	// Item
	CTexture* _item;
	CTexture* _item_stand;

	// Boss
	CTexture* _boss1_bg;
	CTexture* _boss1_badge;

	/*-------- Background -------*/
	vector<int> map1_bg_listTile; // danh sach list file text background
	vector<int> map2_bg_listTile;

	/*--------- Map --------*/
	vector<QTNode*> map1_listNode;
	vector<CObject*> map1_listOb;

	// function
	~CResourcesManager();
	static CResourcesManager *GetInstance();
	static void prepareManager(LPD3DXSPRITE, LPDIRECT3DDEVICE9, HINSTANCE, HWND, CInput*, CAudio*);

	// Menu
	void loadMenuResource();
	void loadMenuGraphics();
	void loadMenuAudio();
	void unloadMenuResource();
	//Loading
	void loadLoadingResource();
	void loadLoadingGraphics();
	void loadLoadingAudio();
	void unloadLoadingResource();
	//Play
	void loadPlayResource();	
	void loadMap1();
	void loadMap2();
	void loadPlayGraphics();
	void loadPlayAudio();
	void unloadPlayResource();
	//Pause
	void loadPauseResource();
	void loadPauseGraphics();
	void loadPauseAudio();
	void unloadPauseResource();
	// Game Over
	void loadOverResource();
	void loadOverGraphics();
	void loadOverAudio();
	void unloadOverResource();


	// load list cac object khong nam trong quad tree
	vector<CObject*> loadFileTextOBNoneTree(string path);
	// load list cac tile tu file text
	vector<int> loadFileTextBG(string path);	
	// load list node tu file text
	vector<QTNode*> loadFileTextNode(string path);
	// load list object tu file text
	vector<CObject*> loadFileTextOB(string path);
	// split string de add vo CObject
	CObject* splitTextPushOB(string str);
	// split string de add vo Node
	QTNode* splitTextPushNode(string str);

	void setLevelMap(int x){ m_levelMap; }

};



#endif