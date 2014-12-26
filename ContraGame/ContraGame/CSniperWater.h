#ifndef _CSNIPER_WATER_H_
#define _CSNIPER_WATER_H_

#include "CEnemyUseGun.h"

class CSniperWater : public CEnemyUseGun
{
protected:
	bool _is_shot;
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);
	void Attacking();
	bool CheckTarget();
public:
	CSniperWater(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CSniperWater();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetTarget(float x, float y);
};

#endif // !_CSNIPER_WATER_H_
