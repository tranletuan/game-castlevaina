#ifndef _SBULLET_H_
#define _SBULLET_H_

#include "CBullet.h"

class CSBullet : public CBullet
{
protected:
	void CalcVelocity(float v_max);

public:
	CSBullet(int id);
	~CSBullet();

	void LoadResources();
	void Draw();
	void Update(float delta_time);
	void Moving(float v_max);
	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
};
#endif // !_SBULLET_H_
