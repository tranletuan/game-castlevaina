#ifndef _CRIFLEMAN1_H_
#define _CRIFLEMAN1_H_

#include "CEnemyUseGun.h"

class CRifleman1 : public CEnemyUseGun
{
protected:
	void DrawWhenAttack();
	void DrawWhenDie();
	void DrawWhenHide();

public:
	CRifleman1(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CRifleman1();

	void LoadResources();
	void Draw();
	void Attacking(CEnemyWaepon* waepon);

};
#endif // !_CRIFLEMAN_H_
