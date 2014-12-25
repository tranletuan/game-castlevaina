#ifndef _CBOSS2_H_
#define _CBOSS2_H_

#include "CBoss2Arm.h"
#include "CEnemyUseGun.h"

class CBoss2 : public CEnemyUseGun
{
protected:
	CSprite*	_destroy_sprite;
	bool		_ready_shoot;
	bool		_is_shot;
	int			_count_time_undying;
	int			_count_time_destroy;

	void DrawWhenWait(D3DXVECTOR3 pos);
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);

	void SetTarget(float x, float y);
	void Attacking();

public:
	CBoss2(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBoss2();

	void LoadResources();
	void Update(int time);
	void Draw();
};
#endif // !_CBOSS2_H_
