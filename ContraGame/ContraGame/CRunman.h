#ifndef _CRUN_MAN_H_
#define _CRUN_MAN_H_

#include "CObject.h"

enum RMStatus
{
	RMStand, RMRun, RMAttack, RMJump, RMDie
};

class CRunman : public CObject
{
protected:
	CSprite* _live_sprite;
	CSprite* _die_sprite;

	void virtual DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenStand(D3DXVECTOR3 pos);
	void DrawWhenRun(D3DXVECTOR3);
	void DrawWhenJump(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	bool SetStatus(RMStatus status);
public:
	CRunman(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CRunman();

	RMStatus _rm_status;
	bool _stand_in_water;
	bool _is_change;

	virtual void LoadResources();
	virtual void Update(int delta_time);
	virtual void SetTarget(D3DXVECTOR3 pos, D3DXVECTOR3 target);
	void Draw();
	bool Jumping();
	void Standing(float y_ground, SpecificType ground_type);
	void Dying();
};
#endif // !_CRUN_MAN_H_
