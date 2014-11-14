#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "CObject.h"
#include "CEnemyWaepon.h"

enum EnemyStatus
{
	Hide, Attack, Die
};

class CEnemy : public CObject
{
protected:
	EnemyStatus _enemy_status;
	D3DXVECTOR3 _target;
	int _hp;

	virtual void DrawWhenHide() = 0;
	virtual void DrawWhenAttack() = 0;
	virtual void DrawWhenDie() = 0;

public:
	CEnemy(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CEnemy();

	virtual void Draw();
	virtual void LoadResources() = 0;
	

	virtual void Attacking(CEnemyWaepon* waepon) = 0;
	virtual void SetTarget(float x, float y);

	
};
#endif // !_CENEMY_H_
