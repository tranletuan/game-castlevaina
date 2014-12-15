#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
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
#include "CDatabase.h"
#include "CResourceID.h"

using namespace std;

class QTNode;
class CObject;
class CCamera;
class CEnemyWeapon;
class CPlayerWeapon;
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
	CDatabase *m_data;
	D3DXVECTOR3 m_posBill;

	int m_curMap;  // map hien tai
	int m_nextMap; // map tiep theo
	int m_life;	
	int m_heightMap;
	int m_widthMap;
	int m_numScore;
	int m_highScore;

	vector<string> _listString; // load tu file confi
	vector<CObject*> listObinView;
	vector<CObject*> listObNoTree; // list ob khong nam trong quad tree
	vector<CObject*> _grounds;
	CPlayerWeapon* _weapon_player1;
	CPlayerWeapon* _weapon_player2;
	CEnemyWeapon* _weapon_enemy;

	/*------    HUD Camera     -----*/
	CTexture *HUD_badge;
	CTexture *HUD_gameover;

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
	CTexture *load_number;
	CTexture *load_stage1;
	CTexture *load_nameStage1;
	CTexture *load_stage2;
	CTexture *load_nameStage2;
	CTexture *load_stage3;
	CTexture *load_nameStage3;

	/*--- Pause Resource ----*/
	CTexture *pause_title;
	CTexture *pause_continue;
	CTexture *pause_end;
	/*--- Game Over Resource ----*/
	CTexture *over_title;
	/*--- Play Resource ----*/
	
	// background
	CTexture *background_1;
	CTexture *background_2;
	CTexture *background_3;

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
	CTexture* _ground_star;
	CTexture* _ground_rock_fly;
	CTexture* _ground_electron;

	//Effect
	CTexture* _effect_destroy;
	CTexture* _effect_shoot;
	CTexture* _effect_die;

	//Enemy
	CTexture* _enemy_sniper_stand;
	CTexture* _enemy_sniper_hide;
	CTexture* _enemy_wall_turret;
	CTexture* _enemy_ground_canon;
	CTexture* _enemy_run_man;
	CTexture* _enemy_fire;
	CTexture* _enemy_rock_roll;

	// Item
	CTexture* _item;
	CTexture* _item_stand;

	// Boss
	CTexture* _boss1_bg;
	CTexture* _boss1_badge;
	CTexture* _boss_gun;

	/*-------- Background -------*/
	vector<int> map_bg_listTile; // danh sach list file text background


	/*--------- Map --------*/	
	vector<QTNode*> map_listNode;
	vector<CObject*> map_listOb;

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

	// load tung ctexture 
	void loadTexture(ResourceID id);
	// get tung ctexture
	CTexture* getTexture(ResourceID id);
	// load all texture object trong map
	void loadAllInMap();
	//  unload all texture object trong map
	void unloadAllInMap();
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

};



#endif