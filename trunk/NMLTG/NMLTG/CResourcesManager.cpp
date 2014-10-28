#include "CResourcesManager.h"

CResourcesManager *CResourcesManager::_instance = 0;

CResourcesManager::CResourcesManager()
{
	//Camera 
	_camera = new CCamera();

	//Contra1
	_bill_stand = new CTexture(L"resources/contra/contra1_stand.png", 5);
	_bill_jump = new CTexture(L"resources/contra/contra1_jump.png", 4);
	_bill_die = new CTexture(L"resources/contra/contra1_die.png", 5);
	_bill_move = new CTexture(L"resources/contra/contra1_move.png", 5, 4);
	_bill_in_water = new CTexture(L"resources/contra/contra1_in_water.png", 5);
}

CResourcesManager::~CResourcesManager()
{
	//camera
	delete _camera;

	//contra1
	delete _bill_stand;
	delete _bill_jump;
	delete _bill_die;
	delete _bill_move;
	delete _bill_in_water;


}

CResourcesManager *CResourcesManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CResourcesManager();
	}

	return _instance;
}


