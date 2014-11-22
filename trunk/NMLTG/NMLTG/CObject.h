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

	CObject(){}
	CObject(int id, SpecificType specific_type, BasicType basic_type, 
		D3DXVECTOR3 pos, int width = 0, int height = 0)
	{
		this->_id = id;
		this->_specific_type = specific_type;
		this->_basic_type = basic_type;
		this->_physical.x = pos.x;
		this->_physical.y = pos.y;
		this->_physical.SetBounds(pos.x, pos.y, width, height);
	}

	virtual void LoadResources() = 0;
	virtual void Draw() = 0;
	//virtual void Update(int delta_time) = 0;
	
};

#endif