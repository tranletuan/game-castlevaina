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
	
	vector<string> _listString; // danh sach string cac texture duoc load len o scene game
	vector<CObject*> listObinView;
	vector<CObject*> listObNoTree; // list ob khong nam trong quad tree
	vector<CObject*> _grounds;
	vector<CObject*> _enemies;
	CPlayerWeapon* _weapon_player1;
	CPlayerWeapon* _weapon_player2;
	CEnemyWeapon* _weapon_enemy;

	/*------    HUD Camera     -----*/
	CTexture *HUD_badge;
	CTexture *HUD_gameover;

	/*------    Sound      -----*/
	CSound *sound_enemy_attacked;
	CSound *sound_bill_1up;
	CSound *sound_bill_dead;
	CSound *sound_boss_dead;
	CSound *sound_stage_clear;
	CSound *sound_get_item;
	CSound *sound_bullet_default;
	CSound *sound_bullet_m;
	CSound *sound_bullet_s;
	CSound *sound_bullet_l;

	/*------    Music      -----*/
	CSound *music_menu_bg;
	CSound *music_map1_bg;
	CSound *music_map2_bg;
	CSound *music_map3_bg;
	CSound *music_gameover_bg;
	CSound *music_win_bg;

	/*--- Menu Resource ----*/
	CTexture *menu_bg;
	CTexture *menu_item1;
	CTexture *menu_item2;
	CTexture *menu_badge;

	

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

	/*--- Win Game Resource ----*/
	CTexture *win_congra;
	CTexture *win_victory;
	CTexture *win_product;
	CTexture *win_tien;
	CTexture *win_tuan;
	CTexture *win_lead;
	CTexture *win_thay;
	CTexture *win_copy;

	/*--- Play Resource ----*/
	
	// background
	CTexture *background;

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
	CTexture* _bullet_b2;
	CTexture* _bullet_b3;
	CTexture* _bullet_sp;

	//Ground
	CTexture* _ground_grass;
	CTexture* _ground_water;	
	CTexture* _ground_auto_destroy_bridge;
	CTexture* _ground_rock_fly;
	CTexture* _ground_electron;


	//Effect
	CTexture* _effect_destroy;
	CTexture* _effect_shoot;
	CTexture* _effect_die;
	CTexture* _effect_waterfall;
	CTexture* _effect_water;
	CTexture* _effect_star;

	//Enemy
	CTexture* _enemy_sniper_stand;
	CTexture* _enemy_sniper_hide;
	CTexture* _enemy_wall_turret;
	CTexture* _enemy_ground_canon;
	CTexture* _enemy_run_man;
	CTexture* _enemy_run_man_fire;
	CTexture* _enemy_fire;
	CTexture* _enemy_rock_roll;
	CTexture* _enemy_sniper_boss;
	CTexture* _enemy_boom_throw;
	CTexture* _enemy_sniper_block;
	CTexture* _enemy_tank;
	CTexture* _enemy_sniper_water;
	// Item
	CTexture* _item;
	CTexture* _item_stand;

	// Boss
	CTexture* _boss1_bg;
	CTexture* _boss1_badge;
	CTexture* _boss1_gun;
	CTexture* _boss2_live;
	CTexture* _boss2_die;
	CTexture* _boss2_elbow;
	CTexture* _boss2_hand;
	CTexture* _boss3;
	CTexture* _boss3_door_die;


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
	// Win Game
	void loadWinResource();
	void loadWinGraphics();
	void loadWinAudio();
	void unloadWinResource();

	/*---------------- method ---------------*/

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
	// doc file confi_default
	void readFileConfiDefault();
	// edit Highscore
	void editHighScoreOfMap();
	// read Highscore
	void readHighScoreOfMap();
};



#endif