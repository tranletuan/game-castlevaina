#ifndef _SBULLET_H_
#define _SBULLET_H_

#include "CBullet.h"

class CSBullet : public CBullet
{
protected: 
	void CalcVelocity(float v_max);

public:
	CSBullet(D3DXVECTOR3 pos, int angle, float direction, float v_max);
	~CSBullet();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void Moving(float v);
};
#endif // !_SBULLET_H_
