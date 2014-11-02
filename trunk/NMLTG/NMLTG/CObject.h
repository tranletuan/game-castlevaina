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

public:
	int				_id;
	SpecificType	_specific_type;
	BasicType		_basic_type;
	CPhysical		_physical;

	CObject(SpecificType specific_type, BasicType basic_type)
	{
		this->_specific_type = specific_type;
		this->_basic_type = basic_type;
	}

	virtual void LoadResources() = 0;
	virtual void Draw() = 0;
};

#endif