#include "CResourcesManager.h"

CResourcesManager *CResourcesManager::_instance = 0;

CResourcesManager::CResourcesManager()
{
	//Camera 
	_camera = new CCamera();

	//Contra1
	_contra1_die = new CTexture(L"resources/contra/contra1_die.png", 5, 1);
	_contra1_in_cave = new CTexture(L"resources/contra/contra1_in_cave.png", 9, 1);
	_contra1_in_water = new CTexture(L"resources/contra/contra1_in_water.png", 5, 1);
	_contra1_jump = new CTexture(L"resources/contra/contra1_jump.png", 4, 1);
	_contra1_run = new CTexture(L"resources/contra/contra1_run.png", 6, 2);
	_contra1_run_up_down = new CTexture(L"resources/contra/contra1_run_up_down.png", 3, 2);
	_contra1_stand = new CTexture(L"resources/contra/contra1_stand.png", 5, 1);
}

CResourcesManager::~CResourcesManager()
{
	//contra1
	delete _contra1_die;
	delete _contra1_in_cave;
	delete _contra1_in_water;
	delete _contra1_jump;
	delete _contra1_run;
	delete _contra1_run_up_down;
	delete _contra1_stand;
}

CResourcesManager *CResourcesManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CResourcesManager();
	}

	return _instance;
}


