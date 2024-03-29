#ifndef _CWAEPON_H_
#define _CWAEPON_H_

#include "CBullet.h"
#include <queue>
#include <map>

class CWaepon
{
protected:
	map<int, CBullet*> _list_bullet;
	queue<int> _queue_id_remove;
	bool CheckBulletInView(float x, float y);

public:
	~CWaepon();

	virtual void RemoveDisabledBullet() = 0;
	virtual CollisionDirection CheckCollision(CObject* obj) = 0;
	
	virtual void LoadResources() = 0;
	void Update(int delta_time);
	void Draw();
};

#endif // !_CBULLET_FACTORY_H_
