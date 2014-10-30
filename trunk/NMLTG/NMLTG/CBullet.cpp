#include "CBullet.h"

CBullet::CBullet(){}

CBullet::~CBullet()
{
	if (_current_sprite != NULL)
	{
		delete _current_sprite;
	}
}

//Góc tối đa là 90 và tối thiểu là -90
CBullet::CBullet(D3DXVECTOR3 pos, int angle, float direction, float v_max)
{
	_physical.x = pos.x;
	_physical.y = pos.y;
	_angle = angle;
	_physical.vx_last = direction;
}

void CBullet::CalcVelocity(float v_max)
{
	if (_angle < -90 || _angle > 90)
	{
		_angle %= 90;
	}

	//2 góc đặc biệt trên dưới
	if (_angle == 90 || _angle == -90)
	{
		_physical.vx = 0;

		if (_angle == 90) _physical.vy = v_max;
		else _physical.vy = -v_max;

		return;
	}

	//2 góc đặt biệt trái phải
	if (_angle == 0)
	{
		_physical.vy = 0;
		_physical.vx = v_max * _physical.vx_last;

		return;
	}

	//Góc bay tính theo tan(a)
	if (_angle != 90 && _angle != -90)
	{
		float _tan = tan(D3DXToRadian(_angle));
		float k = 1 / (1 + _tan * _tan);

		_physical.vx = v_max * sqrt(k) * _physical.vx_last;

		int sign =  _tan > 0 ? 1 : -1;
		_physical.vy = v_max * sqrt(1 - k) * sign;
	}
	
}
