#ifndef _CWAEPON_FACTORY_H_
#define _CWAEPON_FACTORY_H_

#include "CBullet.h"
#include <map>

class CWaeponFactory
{
protected:
	map<string, CBullet*> _list_bullet;
public:
	~CWaeponFactory();

	virtual void Shooting(D3DXVECTOR3 pos, int angle, float direction) = 0;
	virtual CollisionDirection CheckCollision(CObject* obj) = 0;
	virtual void Update(int delta_time);
	virtual void Draw();
	
};

#endif // !_CBULLET_FACTORY_H_
