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
	CEnemyWeapon* _weapon;

	virtual void DrawWhenWait(D3DXVECTOR3 pos) = 0;
	virtual void DrawWhenAttack(D3DXVECTOR3 pos) = 0;
	virtual void DrawWhenDie(D3DXVECTOR3 pos) = 0;
	virtual void Attacking() = 0;
	bool CheckTarget();
	bool SetStatus(EnemyStatus status);

public:
	CEnemy(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CEnemy();
	int _hp;

	virtual void Draw();
	virtual void LoadResources();
	virtual void Update(int delta_time);
	virtual void SetTarget(float x, float y);

	void SetWeapon(CEnemyWeapon* weapon) { _weapon = weapon; }
};
#endif // !_CENEMY_H_
