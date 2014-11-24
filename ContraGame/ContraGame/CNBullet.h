#ifndef _CNORMAL_BULLET_
#define _CNORMAL_BULLET_

#include "CBullet.h"

enum NormalBulletType
{
	PlayerBullet, EnemyBullet
};

class CNBullet : public CBullet
{
protected:
	void CalcVelocity(float v_max);

public:
	CNBullet(int id);
	~CNBullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();

	void Moving(float v_max);
	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);

};
#endif // !_CNORMAL_BULLET_
