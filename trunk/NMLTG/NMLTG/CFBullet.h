#ifndef _CFBULLET_H_
#define _CFBULLET_H_

#include "CBullet.h"
#include "Config.h"

class CFBullet : public CBullet
{
protected:
	void CalcVelocity(float v_max);
	float _x_circle;
	float _y_circle;
	int _degrees;

public:
	CFBullet(D3DXVECTOR3 pos, int angle, float v_max, float vo);
	~CFBullet();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void Moving(float v_max);
};

#endif // !_CFBULLET_H_
