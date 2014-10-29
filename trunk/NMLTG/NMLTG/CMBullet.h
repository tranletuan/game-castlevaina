#ifndef _CMBULLET_H_
#define _CMBULLET_H_

#include "CBullet.h"
class CMBullet : public CBullet
{
protected:
	void CalcVelocity(float v_max);

public:
	CMBullet(D3DXVECTOR3 pos, int angle, float direction, float v_max);
	~CMBullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();
	void Moving(float v);
};
#endif // !_CMBULLET_H_
