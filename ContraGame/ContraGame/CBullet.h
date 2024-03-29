#ifndef _CBULLET_H_
#define _CBULLET_H_

#include "CObject.h"
#include "Config.h"

class CBullet : public CObject
{
protected:
	int _angle;
	float _vo;
	virtual void CalcVelocity(float v_max);
	void SetAngle(int angle);
	void Moving(float v_max);

	CSprite* _ontarget_sprite;
	CSprite* _bullet_sprite;

public:
	CBullet(int id, SpecificType specific_type);
	~CBullet();

	virtual void LoadResources();
	virtual void Update(int delta_time);
	virtual void Draw() = 0;
	virtual void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
	void OnTarget();
};
#endif // !_CBULLET_H_
