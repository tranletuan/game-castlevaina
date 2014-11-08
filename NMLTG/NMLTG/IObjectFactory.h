#ifndef _IOBJECT_FACTORY_H_
#define _IOBJECT_FACTORY_H_

#include "CResourcesManager.h"
#include "CGround.h"
#include "CBill.h"

class IObjectFactory
{
public:
	virtual CGround* GetGround(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height) = 0;
	virtual CBill* GetPlayer(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height) = 0;
};

#endif // !_IOBJECT_FACTORY_H_
