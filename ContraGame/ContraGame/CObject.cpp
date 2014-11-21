#include "CObject.h"

CObject::CObject()
{

}

CObject::CObject(int id, SpecificType specific_type, BasicType basic_type, D3DXVECTOR3 pos, int width , int height )
{
	this->_id = id;
	this->_specific_type = specific_type;
	this->_basic_type = basic_type;
	this->_physical.x = pos.x;
	this->_physical.y = pos.y;
	this->_physical.SetBounds((float)pos.x, (float)pos.y, width, height);
}

CObject::CObject(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
{
	this->_id = id;
	this->_specific_type = specific_type;	
	this->_physical.x = pos.x;
	this->_physical.y = pos.y;
	this->_physical.SetBounds((float)pos.x, (float)pos.y, width, height);
}

void CObject::setSpecificType(string x)
{
	if (x == "Ground")
	{
		setSpecificType(Ground_Grass);
	}	
	else if (x == "Sniper")
	{
		setSpecificType(Sniper_Stand);
	}	
	else if (x == "RunMan")
	{
		setSpecificType(RunMan);
	}
	else if (x == "ItemL")
	{
		setSpecificType(ItemL);
	}
	else if (x == "ItemM")
	{
		setSpecificType(ItemM);
	}
	else if (x == "BradgeEagle")
	{

	}


}

void CObject::Update(int delta_time)
{

}

void CObject::LoadResources()
{

}

void CObject::Draw()
{

}

void CObject::setPos(D3DXVECTOR3 x)
{
	_physical.x = x.x;
	_physical.y = x.y;
}

CObject::~CObject()
{

}