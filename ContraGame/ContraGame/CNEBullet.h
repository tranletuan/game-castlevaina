#ifndef _CNEBULLET_H_
#define _CNEBULLET_H_

#include "CBullet.h"

class CNEBullet : public CBullet
{
protected:
	void CalcVelocity(float v_max);

public:
	CNEBullet(int id);
	~CNEBullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();

	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
};

#endif // !_CNEBULLET_H_
