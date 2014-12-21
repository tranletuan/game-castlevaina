#ifndef _CB2_BULLET_H_
#define _CB2_BULLET_H_

#include "CBullet.h"

class CB2Bullet : public CBullet
{
protected:
	void CalcVelocity(float v_max);
public:
	CB2Bullet(int id);
	~CB2Bullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();

	void Moving(float v_max);
	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
};
#endif // !_CB2_BULLET_H_
