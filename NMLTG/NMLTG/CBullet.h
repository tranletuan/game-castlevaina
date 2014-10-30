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
	virtual void CalcVelocity(float v_max);

public:
	CBullet();
	CBullet(D3DXVECTOR3 pos, int angle, float direction, float v_max);
	~CBullet();

	virtual void LoadResources() = 0;
	virtual void Update(int delta_time) = 0;
	virtual void Draw() = 0;
	virtual void Moving(float v) = 0;
	
};
#endif // !_CBULLET_H_
