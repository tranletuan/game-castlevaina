#ifndef _CBOSS2_ELBOW_H_
#define _CBOSS2_ELBOW_H_

#include "CObject.h"

class CBoss2Elbow : public CObject
{
protected:
	CSprite* _live_sprite;
	CSprite* _die_sprite;

	int _degrees;
	int _last_degrees;
	int _delta_degrees;
	int _radius;

	int _parent_id;
	bool _is_spread;

	float _x_circle;
	float _y_circle;

	void Turning();
public:
	CBoss2Elbow(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBoss2Elbow();

	CBoss2Elbow* _next = NULL;
	CBoss2Elbow* _pre = NULL;
	
	bool _is_active;

	void LoadResources();
	void Update(int time);
	void Draw();
	void Spreading();
	void SetActive(int parent_id, int _direction);
	void SetDeactivate();
	void SetDegrees(int degrees);
};

#endif // !_CHAND_PART_H_
