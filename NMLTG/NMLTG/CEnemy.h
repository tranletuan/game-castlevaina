#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "CObject.h"
#include "CEnemyWeapon.h"

enum EnemyStatus
{
	EWait, EAttack, EDie
};

class CEnemy : public CObject
{
protected:
	EnemyStatus _enemy_status;
	D3DXVECTOR3 _target;

	CSprite* _live_sprite;
	CSprite* _die_sprite;

	virtual void DrawWhenWait(D3DXVECTOR3 pos) = 0;
	virtual void DrawWhenAttack(D3DXVECTOR3 pos) = 0;
	virtual void DrawWhenDie(D3DXVECTOR3 pos) = 0;

public:
	CEnemy(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CEnemy();
	int _hp;

	virtual void Draw();
	virtual void LoadResources() = 0;
	virtual void Attacking(CEnemyWeapon* weapon) = 0;
	virtual void SetTarget(float x, float y);
	
	bool SetStatus(EnemyStatus status);
	bool CheckTarget();
};
#endif // !_CENEMY_H_
