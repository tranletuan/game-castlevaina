#ifndef _COBJECT_MAP_FACTORY_H_
#define _COBJECT_MAP_FACTORY_H_

#include "IObjectFactory.h"
#include "CAutoDestroyBridge.h"

class CObjectMapFactory : public IObjectFactory
{
public:
	CObjectMapFactory();

	CGround* GetGround(int id, SpecificType specific_type, D3DXVECTOR3 pos);
	CBill* GetPlayer(int id, SpecificType specific_type, D3DXVECTOR3 pos);
};

#endif // !_COBJECT_MAP_FACTORY_H_
