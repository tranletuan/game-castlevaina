#ifndef _CENEMY_USE_GUN_H_
#define _CENEMY_USE_GUN_H_

#include "CEnemy.h"

class CEnemyUseGun : public CEnemy
{
protected:

	int _target_angle;
	int _attack_angle;
	int _max_bullet;
	queue<int> _queue_id_bullet; //dùng để kiểm tra số đạn đã bắn
	DWORD _last_time_shoot;

	CSprite* _live_sprite;
	CSprite* _die_sprite;

	virtual void DrawWhenAttack(D3DXVECTOR3 pos) = 0;
	virtual void DrawWhenWait(D3DXVECTOR3 pos) = 0;
	virtual void DrawWhenDie(D3DXVECTOR3 pos) = 0;

public:
	CEnemyUseGun(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CEnemyUseGun();

	virtual void LoadResources() = 0;
	virtual void Draw() = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Attacking(CEnemyWaepon* waepon) = 0;

	void SetTarget(float x, float y);

};
#endif // !_CENEMY_USE_GUN_H_



