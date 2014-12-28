#ifndef _CFB_BULLET_H_
#define _CFB_BULLET_H_

#include "CBullet.h"

class CFBBullet : public CBullet
{
protected:
	void CalcVelocity(float v_max);
public:
	CFBBullet(int id);
	~CFBBullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();
	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
};

#endif // !_CFB_BULLET_H_
