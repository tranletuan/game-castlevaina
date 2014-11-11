#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "CObject.h"

enum StatusEnemy
{
	Hide, Attack, Die
};

class CEnemy : public CObject
{
protected:
	StatusEnemy _status_enemy;

public:
	CEnemy(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
		: CObject(id, specific_type, Enemy, pos, width, height){}
	~CEnemy(){}

	//Override 
	virtual void LoadResources() = 0;
	virtual void Draw() = 0;

	virtual void Attacking() = 0;
	virtual void SetTarget(D3DXVECTOR3 pos) = 0;
};
#endif // !_CENEMY_H_
