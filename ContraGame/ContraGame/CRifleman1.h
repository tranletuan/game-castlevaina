#ifndef _CRIFLEMAN1_H_
#define _CRIFLEMAN1_H_

#include "CEnemyUseGun.h"
#include "IMovableObject.h"

class CRifleman1 : public CEnemyUseGun, public IMovableObject
{
protected:
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);

public:
	CRifleman1(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CRifleman1();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void Attacking(CEnemyWaepon* waepon);
	void Moving(float v);

	
};
#endif // !_CRIFLEMAN_H_
