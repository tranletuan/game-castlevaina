#ifndef _COBJECT_H_
#define _COBJECT_H_

#include "CPhysical.h"
#include "CSprite.h"
#include "CCamera.h"



class CObject
{
protected:
	CSprite* _current_frame;

public:

	CPhysical _physical;
	virtual void LoadResources() = 0;
	virtual void Draw() = 0;
	virtual void Update(int delta_time) = 0;
};

#endif