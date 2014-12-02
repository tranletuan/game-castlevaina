#ifndef _CBOSS_GUN_H_
#define _CBOSS_GUN_H_

#include "CEnemyUseGun.h"

class CBossGun : public CEnemyUseGun
{
protected:
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);
	void Attacking();
public:
	CBossGun(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBossGun();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetTarget(float x, float y);
};
#endif // !_CBOSS_GUN_H_
