#ifndef _CRIFLEMAN2_H_
#define _CRIFLEMAN2_H_

#include "CEnemyUseGun.h"

class CRifleman2 : public CEnemyUseGun
{
protected:
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);

public:
	CRifleman2(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CRifleman2();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void Attacking(CEnemyWeapon* weapon);
	void Moving(float v);

};
#endif // !_CRIFLEMAN2_H_
