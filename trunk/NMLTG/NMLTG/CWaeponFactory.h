#ifndef _CWAEPON_FACTORY_H_
#define _CWAEPON_FACTORY_H_

#include "CBullet.h"
#include <map>

class CWaeponFactory
{
protected:
	map<int, CBullet*> _list_bullet;
	bool CheckBulletInView(float x, float y);
public:
	~CWaeponFactory();

	virtual void Shooting(D3DXVECTOR3 pos, int angle, float vo) = 0;
	virtual void RemoveDisabledBullet() = 0;
	virtual CollisionDirection CheckCollision(CObject* obj) = 0;
	
	virtual void LoadResources() = 0;
	virtual void Update(int delta_time) = 0;
	virtual void Draw() = 0;
	
	
};

#endif // !_CBULLET_FACTORY_H_
