#ifndef _CSNIPER_BOSS_H_
#define _CSNIPER_BOSS_H_

#include "CEnemyUseGun.h"

class CSniperBoss : public CEnemyUseGun
{
protected:
	bool _ready_shoot;
	bool _is_shot;
	bool _is_shooting;
	bool _is_change;

	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);
	void Attacking();
public:
	CSniperBoss(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CSniperBoss();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetTarget(float x, float y);
};
#endif // !_CSNIPER_BOSS_H_
