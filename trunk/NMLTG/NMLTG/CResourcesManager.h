#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "CTexture.h"
#include "CCamera.h"
#include <map>

enum  SpecificType
{
	Player1, Player2, //Player
	BulletN, BulletM, BulletL, BulletF, BulletS, BulletNE, BulletB, //Bullet	
	Ground1, Ground2, Ground3, GroundBridge, //Ground
	EffectDestroy, //Effect
	Solider, Rifleman1, Sniper //Enemy
};

enum BasicType
{
	Player,
	Bullet, 
	Ground,
	Effect,
	Enemy
};

class CResourcesManager
{
private:
	static CResourcesManager *_instance;
	void SetTypeMap();
	CResourcesManager();
	~CResourcesManager();

public:

	static CResourcesManager *GetInstance();
	map<SpecificType, BasicType> _map_type;

	//Camera 
	CCamera* _camera;

	//Background
	CTexture* _background_map1;
	CTexture* _background_map2;
	CTexture* _background_map3;

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
	CTexture* _ground_1;
	CTexture* _ground_2;
	CTexture* _ground_3;
	CTexture* _ground_auto_destroy_bridge;

	//Effect
	CTexture* _effect_destroy;
	CTexture* _effect_shoot;
	CTexture* _effect_die;

	//Enemy
	CTexture* _enemy_rifleman_1;
};

#endif