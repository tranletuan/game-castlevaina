#ifndef _CRUNMAN_FIRE_H_
#define _CRUNMAN_FIRE_H_

#include "CRunman.h"

class CRunmanFire : public CRunman
{
protected:
	void DrawWhenStand(D3DXVECTOR3 pos);
	void DrawWhenRun(D3DXVECTOR3);
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenJump(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
public:
	CRunmanFire(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CRunmanFire();

	void Draw();
	void LoadResources();
	void Update(int delta_time);
	void SetTarget(D3DXVECTOR3 pos, D3DXVECTOR3 target);
};
#endif // !_CRUNMAN_FIRE_H_
