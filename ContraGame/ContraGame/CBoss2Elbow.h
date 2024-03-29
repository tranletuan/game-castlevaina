#ifndef _CBOSS2_ELBOW_H_
#define _CBOSS2_ELBOW_H_

#include "CObject.h"

class CBoss2Elbow : public CObject
{
protected:
	CSprite* _live_sprite;
	CSprite* _die_sprite;

	int _degrees;
	int _delta_degrees;
	float _radius;
	float _delta_radius;

	float _x_circle;
	float _y_circle;

	void Turning();
	void CalRadius(int degrees, int pre_degrees);
public:
	CBoss2Elbow(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height, int direction);
	~CBoss2Elbow();

	CBoss2Elbow* _next = NULL;
	CBoss2Elbow* _pre = NULL;
	
	bool _is_active;

	void LoadResources();
	virtual void Update(int time);
	void Draw();
	void Spreading(int parent_id);
	void SetActive();
	void SetDeactivate();
	void SetDegrees(int degrees);
	bool Boot(int time);
};

#endif // !_CHAND_PART_H_
