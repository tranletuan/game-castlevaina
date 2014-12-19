#ifndef _CBOSS1_GUN_H_
#define _CBOSS1_GUN_H_

#include "CEnemyUseGun.h"

class CBoss1Gun : public CEnemyUseGun
{
protected:
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);
	void Attacking();
public:
	CBoss1Gun(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBoss1Gun();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetTarget(float x, float y);
};
#endif // !_CBOSS_GUN_H_
