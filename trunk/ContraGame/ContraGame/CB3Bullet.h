#ifndef _CB3_BULLET_H_
#define _CB3_BULLET_H_

#include "CBullet.h"

class CB3Bullet : public CBullet
{
protected:
	float	_x_shoot;
	bool	_is_fall;

	void CalcVelocity(float v_max);
public:
	CB3Bullet(int id);
	~CB3Bullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();
	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
};

#endif // !_CB3_BULLET_H_
