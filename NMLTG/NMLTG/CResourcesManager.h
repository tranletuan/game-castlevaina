#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "CTexture.h"
#include "CCamera.h"

enum  SpecificType
{
	Player1, Player2, //Player
	BulletN, BulletM, BulletL, BulletF, BulletS, //Bullet
	Ground1, Ground2, Ground3, GroundBridge, //Ground
	EffectDestroy //Effect
};

enum BasicType
{
	Player,
	Bullet, 
	Ground,
	Effect
};

class CResourcesManager
{
private:
	static CResourcesManager *_instance;
	CResourcesManager();
	~CResourcesManager();

public:

	static CResourcesManager *GetInstance();
	
	//Camera 
	CCamera* _camera;

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

	//Ground
	CTexture* _ground_1;
	CTexture* _ground_2;
	CTexture* _ground_3;
	CTexture* _ground_auto_destroy_bridge;

	//Effect
	CTexture* _effect_destroy;
};

#endif