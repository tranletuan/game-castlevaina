#ifndef CTANK_H
#define CTANK_H

#include "CEnemyUseGun.h"


class CTank
	: public CEnemyUseGun
{
private:
	float _distance_move; // khoảng cách di chuyển
	int _count; // đếm số lần bắn

public:
	CTank(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CTank();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetTarget(float x, float y);

	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void Attacking();

	
};


#endif
