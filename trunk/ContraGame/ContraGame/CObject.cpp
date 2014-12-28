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
	this->_can_impact = false;
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
	this->_can_impact = false;
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
	this->_can_impact = false;
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
	else if (x == "RunManFire")
	{
		setSpecificType(RunMan_Fire);
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
	else if (x == "ItemL")
	{
		setSpecificType(ItemL);
	}
	else if (x == "ItemStandM")
	{
		setSpecificType(ItemM_Stand);
	}
	else if (x == "ItemStandF")
	{
		setSpecificType(ItemF_Stand);
	}
	else if (x == "ItemStandS")
	{
		setSpecificType(ItemS_Stand);
	}
	else if (x == "ItemStandB")
	{
		setSpecificType(ItemB_Stand);
	}
	else if (x == "ItemStandL")
	{
		setSpecificType(ItemL_Stand);
	}
	else if (x == "WaterEffect1")
	{
		setSpecificType(Effect_Water);
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
	else if (x == "Brigde")
	{
		setSpecificType(Ground_Bridge);
	}	
	else if (x == "Water")
	{
		setSpecificType(Ground_Water);
	}
	else if (x == "StarEffect")
	{
		setSpecificType(Effect_Star);
	}
	else if (x == "GroundElectron")
	{
		setSpecificType(Ground_Electron);
	}
	else if (x == "Fire")
	{
		setSpecificType(Fire_Run);
	}
	else if (x == "Boss1Gun")
	{
		setSpecificType(Boss1_Gun);
	}
	else if (x == "RockRoll")
	{
		setSpecificType(Rock_Roll);
	}
	else if (x == "RockFly")
	{
		setSpecificType(Ground_RockFly);
	}
	else if (x == "SniperBoss")
	{
		setSpecificType(Sniper_Boss);
	}
	else if (x == "Boom")
	{
		setSpecificType(Boom_Throw);
	}
	else if (x == "SniperBlock")
	{
		setSpecificType(Sniper_Block);
	}
	else if (x == "WaterFall")
	{
		setSpecificType(Effect_WaterFall);
	}
	else if (x == "Tank")
	{
		setSpecificType(Tank);
	}
	else if (x == "SniperWater")
	{
		setSpecificType(Sniper_Water);
	}
	else if (x == "Boss2")
	{
		setSpecificType(Boss2);
	}
	else if (x == "Boss2Arm")
	{
		setSpecificType(Boss2_Arm);
	}
	else if (x == "Boss3")
	{
		setSpecificType(Boss3);
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

CollisionDirection CObject::CheckCollision(CObject* ob)
{
	vector<CPhysical> ob_elements = ob->GetListElement();
	CollisionDirection cd = NoCollision;
	for (vector<CPhysical>::iterator i = ob_elements.begin(); i != ob_elements.end(); i++)
	{
		cd = _physical.Collision(&(*i));
	}

	return cd;
}

vector<CPhysical> CObject::GetListElement()
{
	vector<CPhysical> list;
	list.push_back(_physical);
	return list;
}

void CObject::setPos(D3DXVECTOR3 x)
{
	_physical.x = x.x;
	_physical.y = x.y;
}

CObject::~CObject()
{

}