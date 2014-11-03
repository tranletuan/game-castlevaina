#include "CBullet.h"

CBullet::~CBullet()
{
	if (_current_sprite != NULL)
	{
		delete _current_sprite;
	}
}

//Góc tối đa là 90 và tối thiểu là -90
CBullet::CBullet(SpecificType specific_type, D3DXVECTOR3 pos, int angle, float v_max, float vo)
	:CObject(-1, specific_type, Bullet, pos)
{
	_vo = vo;
	SetAngle(angle);
}

void CBullet::SetAngle(int angle)
{
	this->_angle = angle;

	//Đưa góc nhập vào về góc trong khoảng 0->359
	if (_angle < 0 || _angle >= 360)
	{
		_angle %= 360;

		if (_angle < 0)
		{
			_angle += 360;
		}
	}

	//Tính hướng bay
	if (_angle > 270 || _angle < 90)
	{
		_physical.vx_last = 1;
	}
	else
	{
		_physical.vx_last = -1;
	}
}

void CBullet::CalcVelocity(float v_max)
{
	//2 góc đặc biệt trên dưới
	if (_angle == 90 || _angle == 270)
	{
		_physical.vx = 0;

		if (_angle == 90) _physical.vy = v_max;
		else _physical.vy = -v_max;

		return;
	}

	//2 góc đặt biệt trái phải
	if (_angle == 0 || _angle == 180)
	{
		_physical.vy = 0;
		_physical.vx = _physical.vx_last > 0 ? v_max : -v_max;
		_physical.vx += _vo;
		return;
	}

	//Góc bay tính theo tan(a)
	if (_angle != 90 && _angle != 270)
	{
		float _tan = tan(D3DXToRadian(_angle));
		float k = 1 / (1 + _tan * _tan);

		_physical.vx = v_max * sqrt(k);
		_physical.vx = _physical.vx_last > 0 ? _physical.vx : -_physical.vx;

		int sign = _tan *_physical.vx > 0 ? 1 : -1;
		_physical.vy = v_max * sqrt(1 - k) * sign;
		_physical.vx += _vo; //Tổng vận tốc tọa độ gốc di chuyển và đạn di chuyển
	}
	
	
}
