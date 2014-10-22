#ifndef _COBJECT_H_
#define _COBJECT_H_

#include "CPhysical.h"
#include "CResourcesManager.h"



class CObject
{
protected:
	CSprite* _current_sprite;

public:

	CPhysical _physical;
	virtual void LoadResources() = 0;
	virtual void Draw() = 0;
	virtual void Update(int delta_time) = 0;
};

#endif