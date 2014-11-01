#ifndef _LBULLET_H_
#define _LBULLET_H_

#include "CBullet.h"

class CLBullet : public CBullet
{
protected:
	D3DXVECTOR2 _scale;
	void CalcVelocity(float v_max);
public:
	CLBullet(D3DXVECTOR3 pos, int angle, float v_max, float vo);
	~CLBullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();
	void Moving(float v_max);
};

#endif // !_LBULLET_H_
