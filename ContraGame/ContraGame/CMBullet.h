#ifndef _CMBULLET_H_
#define _CMBULLET_H_

#include "CBullet.h"
class CMBullet : public CBullet
{
protected:
	void CalcVelocity(float v_max);

public:
	CMBullet(int id);
	~CMBullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();

	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
};
#endif // !_CMBULLET_H_
