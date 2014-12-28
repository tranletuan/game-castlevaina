#ifndef _CBOSS3_H_
#define _CBOSS3_H_

#include "CEnemyUseGun.h"

class CBoss3 : public CEnemyUseGun
{
protected:
	DWORD _last_time_shoot_fb;
	DWORD _last_time_shoot_b3;
	DWORD _last_time_hide;
	DWORD _last_time_appear;

	bool	_is_hide;
	bool	_ready_shoot;
	int		_count_time_destroy;
	float	_x_random;
	float	_y_random;

	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);
	void Attacking();
public:
	CBoss3(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBoss3();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetTarget(float x, float y);
};
#endif // !_CBOSS3_H_
