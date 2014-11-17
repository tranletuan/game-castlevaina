#ifndef _CENEMY_WAEPON_H_
#define _CENEMY_WAEPON_H_

#include "CWaepon.h"
#include "CNEBullet.h"
#include "CBBullet.h"

class CEnemyWaepon : public CWaepon
{
protected:
	queue<CBullet*> _queue_bullet_ne;
	queue<CBullet*> _queue_bullet_b;

public:
	CEnemyWaepon();
	~CEnemyWaepon();

	void LoadResources();
	void RemoveDisabledBullet();
	CollisionDirection CheckCollision(CObject* obj);
	void UpdateQueueIdBullet(queue<int> &queue_id_bullet);

	int ShootingBulletNE(D3DXVECTOR3 pos, int angle, float vo);
	int ShootingBulletB(D3DXVECTOR3 pos, int angle, float vo);
};
#endif // !_CENEMY_WAEPON_H_
