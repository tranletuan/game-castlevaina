#ifndef _CNORMAL_BULLET_
#define _CNORMAL_BULLET_

#include "CBullet.h"

enum NormalBulletType
{
	PlayerBullet, EnemyBullet
};

class CNormalBullet : public CBullet
{
public:
	CNormalBullet(D3DXVECTOR3 pos, int angle, float direction);
	~CNormalBullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();
	void Moving(float vx);
};
#endif // !_CNORMAL_BULLET_
