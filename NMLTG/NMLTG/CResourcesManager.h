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
	CTexture* _bill_stand;
	CTexture* _bill_jump;
	CTexture* _bill_die;
	CTexture* _bill_move;
	CTexture* _bill_in_water;
};

#endif