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
	this->_track = Track_LR;
	this->_enable = false;
}

CObject::CObject(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
{
	this->_id = id;
	this->_specific_type = specific_type;	
	this->_physical.x = pos.x;
	this->_physical.y = pos.y;
	this->_physical.SetBounds((float)pos.x, (float)pos.y, width, height);
	this->_track = Track_LR;
	this->_enable = false;
}

CObject::CObject(int id, SpecificType specific_type, D3DXVECTOR3 pos, TrackID track, int width, int height)
{
	this->_id = id;
	this->_specific_type = specific_type;
	this->_physical.x = pos.x;
	this->_physical.y = pos.y;
	this->_physical.SetBounds((float)pos.x, (float)pos.y, width, height);
	this->_track = track;
	this->_enable = false;
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
	else if (x == "ItemR")
	{
		setSpecificType(ItemR);
	}
	else if (x == "ItemM")
	{
		setSpecificType(ItemM);
	}
	else if (x == "ItemS")
	{
		setSpecificType(ItemS);
	}
	else if (x == "ItemB")
	{
		setSpecificType(ItemB);
	}
	else if (x == "ItemStandM")
	{
		setSpecificType(ItemM_Stand);
	}
	else if (x == "WaterEffect1")
	{
		setSpecificType(Ground_Effect1);
	}
	else if (x == "BlockHouse")
	{
		setSpecificType(Wall_Turret);
	}
	else if (x == "SniperHide")
	{
		setSpecificType(Sniper_Hide);
	}
	else if (x == "Obstacle")
	{
		setSpecificType(Ground_Canon);
	}
	else if (x == "Boss1")
	{
		setSpecificType(Boss1);
	}

	
}

void CObject::setTrack(string x)
{
	if (x =="0")
	{
		_track = Track_LR;
	}
	else if (x == "1")
	{
		_track = Track_RL;
	}
	else if (x == "2")
	{
		_track = Track_UD;
	}
	else if (x == "3")
	{
		_track = Track_DU;
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