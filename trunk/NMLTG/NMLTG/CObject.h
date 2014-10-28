#ifndef _COBJECT_H_
#define _COBJECT_H_

#include "CPhysical.h"
#include "CResourcesManager.h"
#include <string>

using namespace std;

class CObject
{
protected:
	CSprite* _current_sprite;
	int _id;
	string _type;

public:

	CPhysical _physical;
	virtual void LoadResources() = 0;
	virtual void Draw() = 0;
};

#endif