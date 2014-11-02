#ifndef _CBULLET_H_
#define _CBULLET_H_
#include "CObject.h"
#include "IMovableObject.h"
#include "CResourcesManager.h"
#include "Config.h"

class CBullet : public CObject, public IMovableObject
{
protected:
	int _angle;
	float _vo;
	virtual void CalcVelocity(float v_max);
	void SetAngle(int angle);

public:
	CBullet(SpecificType specific_type, D3DXVECTOR3 pos, int angle, float v_max, float vo);
	~CBullet();

	virtual void LoadResources() = 0;
	virtual void Update(int delta_time) = 0;
	virtual void Draw() = 0;
	virtual void Moving(float v_max) = 0;
	
};
#endif // !_CBULLET_H_
