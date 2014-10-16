#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "CTexture.h"
#include "CCamera.h"

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
	CTexture* _contra1_die;
	CTexture* _contra1_in_cave;
	CTexture* _contra1_in_water;
	CTexture* _contra1_jump;
	CTexture* _contra1_move_deep;
	CTexture* _contra1_run;
	CTexture* _contra1_run_up_down;
	CTexture* _contra1_stand;
};

#endif