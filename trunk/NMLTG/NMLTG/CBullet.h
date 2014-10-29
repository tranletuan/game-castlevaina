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
	void CalcVelocity(float v);
public:
	CBullet();
	CBullet(D3DXVECTOR3 pos, int angle, float direction);

	virtual void LoadResources();
	virtual void Update(int delta_time);
	virtual void Draw();
	virtual void Moving(float v);

};
#endif // !_CBULLET_H_
