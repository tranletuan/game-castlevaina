#ifndef _CRUNMAN_FIRE_H_
#define _CRUNMAN_FIRE_H_

#include "CRunman.h"
#include "CEnemyWeapon.h"
#include <queue>

class CRunmanFire : public CRunman
{
protected:
	int _target_angle;
	int _attack_angle;
	int _max_bullet;
	queue<int> _queue_id_bullet; //dùng để kiểm tra số đạn đã bắn
	CEnemyWeapon* _weapon;
	CSprite* _attack_sprite;

	void DrawWhenStand(D3DXVECTOR3 pos);
	void DrawWhenRun(D3DXVECTOR3);
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenJump(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void Attacking();
	void SetWeapon(CEnemyWeapon* weapon) { _weapon = weapon; }

public:
	CRunmanFire(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CRunmanFire();

	void Draw();
	void LoadResources();
	void Update(int delta_time);
	void SetTarget(D3DXVECTOR3 pos, D3DXVECTOR3 target);
};
#endif // !_CRUNMAN_FIRE_H_
