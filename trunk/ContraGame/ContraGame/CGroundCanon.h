#ifndef _CGROUND_CANON_H_
#define _CGROUND_CANON_H_

#include "CEnemyUseGun.h"

class CGroundCanon : public CEnemyUseGun
{
protected:
	bool _ready_shoot;
	bool _can_shoot; //Góc 
	bool _is_hide;
	int _real_angle;

	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);
	void Attacking();

public:
	CGroundCanon(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CGroundCanon();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetTarget(float x, float y);
	bool CheckCorrectAngle();
	int GetIndexSpriteByAngle(int angle);
};
#endif // !_CGROUND_CANON_H_
