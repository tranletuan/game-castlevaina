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
	CFBullet(int id);
	~CFBullet();

	void LoadResources();
	void Draw();
	void Update(float delta_time);
	void Moving(float v_max);
	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
};

#endif // !_CFBULLET_H_
