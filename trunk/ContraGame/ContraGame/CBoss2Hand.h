#ifndef _CBOSS2_HAND_H_
#define _CBOSS2_HAND_H_

#include "CBoss2Elbow.h"
#include "CEnemyWeapon.h"

class CBoss2Hand : public CBoss2Elbow
{
protected:
	CEnemyWeapon* _weapon;
	D3DXVECTOR3 _target;
	queue<int> _queue_id_bullet;
	DWORD _last_time_shoot;
	int _attack_angle;
	int _target_angle;
	int _max_bullet;

	bool CheckTarget();
	void SetTarget(float x, float y);
	void Attacking();
public:
	CBoss2Hand(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height, int direction);
	~CBoss2Hand();

	void Update(int time);

	void SetWeapon(CEnemyWeapon* weapon) { _weapon = weapon; }
};
#endif // !_CBOSS2_HAND_H_
