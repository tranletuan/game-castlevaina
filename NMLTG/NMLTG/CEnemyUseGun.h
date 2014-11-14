#ifndef _CENEMY_USE_GUN_H_
#define _CENEMY_USE_GUN_H_

#include "CEnemy.h"

class CEnemyUseGun : public CEnemy
{
protected:
	int _target_angle;
	CSprite* _live_sprite;
	CSprite* _die_sprite;

	virtual void DrawWhenAttack() = 0;
	virtual void DrawWhenHide() = 0;
	virtual void DrawWhenDie() = 0;

public:
	CEnemyUseGun(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CEnemyUseGun();

	virtual void LoadResources() = 0;
	virtual void Draw() = 0;
	virtual void Attacking(CEnemyWaepon* waepon) = 0;

	void SetTarget(float x, float y);

};
#endif // !_CENEMY_USE_GUN_H_



