#ifndef _CRIFLEMAN1_H_
#define _CRIFLEMAN1_H_

#include "CEnemyUseGun.h"

class CSniperStand : public CEnemyUseGun
{
protected:
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);

public:
	CSniperStand(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CSniperStand();

	void LoadResources();
	void Draw();
	void Update(float delta_time);

	void Attacking(CEnemyWaepon* waepon);
	
};
#endif // !_CRIFLEMAN_H_
