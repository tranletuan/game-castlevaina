#ifndef _LBULLET_H_
#define _LBULLET_H_

#include "CBullet.h"

class CLBullet : public CBullet
{
protected:
	D3DXVECTOR2 _scale;
	void CalcVelocity(float v_max);
public:
	CLBullet(int id);
	~CLBullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();
	void Moving(float v_max);
	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
};

#endif // !_LBULLET_H_
