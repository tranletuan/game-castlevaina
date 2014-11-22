#include "CResourcesManager.h"

CResourcesManager *CResourcesManager::_instance = 0;

CResourcesManager::CResourcesManager()
{
	SetTypeMap();

	//Camera 
	_camera = new CCamera();

	//Player
	_bill_stand = new CTexture(L"resources/player/bill_stand.png", 5);
	_bill_jump = new CTexture(L"resources/player/bill_jump.png", 4);
	_bill_die = new CTexture(L"resources/player/bill_die.png", 5);
	_bill_move = new CTexture(L"resources/player/bill_move.png", 5, 4);
	_bill_in_water = new CTexture(L"resources/player/bill_in_water.png", 5);

	//Bullet
	_bullet_n = new CTexture(L"resources/bullet/bullet_n.png");
	_bullet_s = new CTexture(L"resources/bullet/bullet_s.png", 3);
	_bullet_l = new CTexture(L"resources/bullet/bullet_l.png");
	_bullet_f = new CTexture(L"resources/bullet/bullet_f.png");
	_bullet_m = new CTexture(L"resources/bullet/bullet_m.png");
	_bullet_ne = new CTexture(L"resources/bullet/bullet_ne.png");
	_bullet_b = new CTexture(L"resources/bullet/bullet_b.png");

	//Ground
	_ground_1 = new CTexture(L"resources/ground/ground1.png");
	_ground_2 = new CTexture(L"resources/ground/ground2.png", 2);
	_ground_3 = new CTexture(L"resources/ground/ground3.png", 2);
	_ground_auto_destroy_bridge = new CTexture(L"resources/ground/ground_bridge.png", 1, 6);

	//Effect
	_effect_destroy = new CTexture(L"resources/effect/effect_destroy.png", 3);
	_effect_shoot = new CTexture(L"resources/effect/effect_shoot.png");
	_effect_die = new CTexture(L"resources/effect/effect_die.png", 3);

	//Enemy
	_enemy_rifleman_1 = new CTexture(L"resources/enemy/rifleman1.png", 5);
	_enemy_rifleman_2 = new CTexture(L"resources/enemy/rifleman2.png", 5);
}

CResourcesManager::~CResourcesManager()
{
	_map_type.clear();

	//camera
	delete _camera;

	//player
	delete _bill_stand;
	delete _bill_jump;
	delete _bill_die;
	delete _bill_move;
	delete _bill_in_water;

	//bullet
	delete _bullet_n;
	delete _bullet_s;
	delete _bullet_l;
	delete _bullet_f;
	delete _bullet_m;

	//ground
	delete _ground_1;
	delete _ground_2;
	delete _ground_3;
	delete _ground_auto_destroy_bridge;

	//effect
	delete _effect_destroy;
	delete _effect_shoot;
	delete _effect_die;

	//enemy
	delete _enemy_rifleman_1;
	delete _enemy_rifleman_2;
}

CResourcesManager *CResourcesManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CResourcesManager();
	}

	return _instance;
}

void CResourcesManager::SetTypeMap()
{
	//Player
	_map_type[Player1] = Player;
	_map_type[Player2] = Player;

	//Bullet
	_map_type[BulletN] = Bullet;
	_map_type[BulletM] = Bullet;
	_map_type[BulletL] = Bullet;
	_map_type[BulletF] = Bullet;
	_map_type[BulletS] = Bullet;

	//Ground
	_map_type[Ground1] = Ground;
	_map_type[Ground2] = Ground;
	_map_type[Ground3] = Ground;
	_map_type[GroundBridge] = Ground;

	//Effect
	_map_type[EffectDestroy] = Effect;
}


