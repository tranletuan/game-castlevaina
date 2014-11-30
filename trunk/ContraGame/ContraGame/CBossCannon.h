#ifndef CBOSSCANNON_H
#define CBOSSCANNON_H

#include "CEnemyUseGun.h"

class CBossCannon
	: public CEnemyUseGun
{
protected:
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);
	void Attacking();
public:
	CBossCannon(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBossCannon();

	void LoadResources();
	void Draw();
	void Update(int delta_time);


};



#endif