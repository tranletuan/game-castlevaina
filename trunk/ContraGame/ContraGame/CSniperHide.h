#ifndef _CSNIPER_HIDE_H_
#define _CSNIPER_HIDE_H_

#include "CEnemyUseGun.h"

class CSniperHide : public CEnemyUseGun
{
protected:
	bool _ready_shoot;
	bool _is_shot;

	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);
	void Attacking();
public:
	CSniperHide(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CSniperHide();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetTarget(float x, float y);

};
#endif // !_CSNIPER_HIDE_H_
