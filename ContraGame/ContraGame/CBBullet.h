#ifndef _CBBULET_H_
#define _CBBULET_H_

#include "CBullet.h"
#include <stdlib.h>

class CBBullet : public CBullet
{
protected:
	void CalcVelocity(float v_max);

public:
	CBBullet(int id);
	~CBBullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();

	void Moving(float v_max);
	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
};
#endif // !_CBBULET_H_
