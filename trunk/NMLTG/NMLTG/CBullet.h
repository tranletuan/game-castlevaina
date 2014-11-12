#ifndef _CBULLET_H_
#define _CBULLET_H_
#include "CObject.h"
#include "IMovableObject.h"
#include "CResourcesManager.h"
#include "Config.h"

class CBullet : public CObject, public IMovableObject
{
protected:
	int _angle;
	float _vo;
	virtual void CalcVelocity(float v_max);
	void SetAngle(int angle);
	CSprite* _ontarget_sprite;
	CSprite* _bullet_sprite;
	
public:
	CBullet(int id, SpecificType specific_type);
	~CBullet();

	virtual void LoadResources();
	virtual void Update(int delta_time) = 0;
	virtual void Draw() = 0;
	virtual void Moving(float v_max) = 0;
	virtual void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
	void OnTarget();
	
	bool _enable;
	
};
#endif // !_CBULLET_H_
