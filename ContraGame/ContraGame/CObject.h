#ifndef _COBJECT_H_
#define _COBJECT_H_

#include "Physical.h"
#include "CResourcesManager.h"
#include <string>
#include "CObjectID.h"

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
	bool			_enable; // đang hoạt động, để xử lý update cho nhung ob o ngoai quad tree
	TrackID			_track;
	int				_hp;
	bool			_can_impact;

	CObject();
	CObject(int id, SpecificType specific_type, BasicType basic_type,D3DXVECTOR3 pos, int width = 0, int height = 0);
	CObject(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	CObject(int id, SpecificType specific_type, D3DXVECTOR3 pos, TrackID track ,int width, int height);
	~CObject();
	
	virtual void LoadResources();
	virtual void Draw();
	virtual void Update(int delta_time);

	SpecificType getSpecificType(){ return _specific_type; }
	void setSpecificType(SpecificType x){ _specific_type = x; }	
	BasicType getBasicType(){ return _basic_type; }
	void setBasicType(BasicType x){ _basic_type = x; }
	int getID(){ return _id; }
	void setID(int x){ _id = x; }
	void setPosX(float x){ _physical.x = x; }
	float getPosX(){ return _physical.x; }
	void setPosY(float  x){ _physical.y = x; }
	float getPosY(){ return _physical.y; }
	void setWidth(int x){ _physical._width = x; }
	int getWidth(){ return _physical._width; }
	void setHeight(int x){ _physical._height = x; }
	int getHeight(){ return _physical._height; }
	void setEnable(bool x){ _enable = x; }
	bool getEnable(){ return _enable; }
	void setTrack(TrackID x){ _track = x; }	
	TrackID getTrack(){ return _track; }

	D3DXVECTOR3 getPos(){ return D3DXVECTOR3(_physical.x, _physical.y, 0); }
	void setPos(D3DXVECTOR3 x);
	void setSpecificType(string x);
	void setTrack(string x);

};

#endif