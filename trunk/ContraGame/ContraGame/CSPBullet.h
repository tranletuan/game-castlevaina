#ifndef _CSPBULLET_H_
#define _CSPBULLET_H_

#include "CBullet.h"

class CSPBullet : public CBullet
{
protected:
	CSprite*	_split_sprite;
	float		_vx_split;
	float		_y_shoot;
	int			_max_altitude;
	bool		_is_split;
	D3DXVECTOR3 _pos_split;

	void CalcVelocity(float v_max);
public:
	CSPBullet(int id);
	~CSPBullet();

	void LoadResources();
	void Update(int delta_time);
	void Draw();
	void Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo = 0);
};
#endif // !_CBULLET_SPLIT_H_
