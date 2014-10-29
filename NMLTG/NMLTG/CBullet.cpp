#include "CBullet.h"

CBullet::CBullet(){}

//Góc tối đa là 90 và tối thiểu là -90
CBullet::CBullet(D3DXVECTOR3 pos, int angle, float direction)
{
	_physical.x = pos.x;
	_physical.y = pos.y;
	_angle = angle;
	_physical.vx_last = direction;
}

void CBullet::CalcVelocity(float v)
{
	if (_angle < -90 || _angle > 90)
	{
		_angle %= 90;
	}

	//2 góc đặc biệt trên dưới
	if (_angle == 90 || _angle == -90)
	{
		_physical.vx = 0;

		if (_angle == 90) _physical.vy = v;
		else _physical.vy = -v;

		return;
	}

	//2 góc đặt biệt trái phải
	if (_angle == 0)
	{
		_physical.vy = 0;
		_physical.vx = v * _physical.vx_last;

		return;
	}

	//Góc bay tính theo tan(a)
	if (_angle != 90 && _angle != -90)
	{
		float _tan = tan(D3DXToRadian(_angle));
		float k = 1 / (1 + _tan * _tan);

		_physical.vx = v * sqrt(k) * _physical.vx_last;

		int sign =  _tan > 0 ? 1 : -1;
		_physical.vy = v * sqrt(1 - k) * sign;
	}
	
}

void CBullet::LoadResources(){}
void CBullet::Update(int delta_time){}
void CBullet::Draw(){}
void CBullet::Moving(float v){}