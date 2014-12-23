#include "CBoss2Elbow.h"

CBoss2Elbow::CBoss2Elbow(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height, int direction)
	: CObject(id, specific_type, Enemy, pos, width, height)
{
	_hp = 1;
	_is_active = true;
	_delta_radius = 0;
	_x_circle = _physical.x;
	_y_circle = _physical.y;
	_physical.vx_last = direction;
	_physical.vx = direction > 0 ? BOSS2_V_BOOT : -BOSS2_V_BOOT;
	_physical.vy = BOSS2_V_BOOT;
	_degrees = direction > 0 ? 45 : 135;
	LoadResources();
}

CBoss2Elbow::~CBoss2Elbow()
{
}

void CBoss2Elbow::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	if (_specific_type == Boss2_Elbow)
	{
		_live_sprite = new CSprite(rs->_boss2_elbow);
	}
	else if (_specific_type == Boss2_Hand)
	{
		_live_sprite = new CSprite(rs->_boss2_hand);
	}

	_die_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _live_sprite;
	_radius = rs->_boss2_elbow->frame_width - 1;
	_delta_radius = _id * (rs->_boss2_elbow->frame_width - 1);
	_delta_degrees = 15;
}

void CBoss2Elbow::Update(int time)
{
	if (_hp > 0)
	{
		if (_is_active)
		{
			Turning();
		}

		//Tính toán góc quay
		_x_circle = _physical.x + _delta_radius * cos(D3DXToRadian(_degrees));
		_y_circle = _physical.y + _delta_radius * sin(D3DXToRadian(_degrees));
		_physical.SetBounds(
			_x_circle,
			_y_circle,
			_current_sprite->sprite_texture->frame_width,
			_current_sprite->sprite_texture->frame_height);

	}
	else if (_hp <= 0)
	{
		_current_sprite = _die_sprite;
		_physical.SetBounds(0, 0, 0, 0);
	}
}

void CBoss2Elbow::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_x_circle, _y_circle);
	if (_hp > 0)
	{
		_current_sprite->Draw(pos.x, pos.y);
	}
	else
	{
		bool _enable = !_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 2);
	}
}

void CBoss2Elbow::Turning()
{
	if (_physical.vx_last > 0)
	{
		_degrees += BOSS2_DELTA_ANGLE;
	}
	else
	{
		_degrees -= BOSS2_DELTA_ANGLE;
	}

	//Thiết lập để góc quay nằm trong khoảng 0 -> 360
	SetDegrees(_degrees);
	
	//Tính bán kính hoạt động sao cho các hình tròn luôn tiếp xúc nhau
	if (_pre != NULL && _pre->_id > 0)
	{
		CalRadius(_degrees, _pre->_degrees);
	}
}

void CBoss2Elbow::SetDeactivate()
{
	_is_active = false;
	_physical.vx_last *= -1;
}

void CBoss2Elbow::SetActive()
{
	_is_active = true;
}

void CBoss2Elbow::Spreading(int parent_id)
{
	if (_delta_degrees <= 0) return;

	if (_next != NULL && _next->_id != parent_id)
	{
		int angle1 = _physical.vx_last > 0 ? _degrees : _next->_degrees;
		int angle2 = _physical.vx_last > 0 ? _next->_degrees : _degrees;

		if (angle1 > 270 && angle2 < 90)
		{
			angle2 += 360;
		}

		if (angle1 < 90 && angle2 > 270)
		{
			angle1 += 360;
		}

		if (angle1 - angle2 >= _delta_degrees)
		{
			if (_is_active)
			{
				int delta = _physical.vx_last > 0 ? -_delta_degrees : _delta_degrees;
				_next->SetDegrees(_degrees + delta);
				_next->SetActive();
				_next->_physical.vx_last = _physical.vx_last;
			}
			else
			{
				int delta = _physical.vx_last > 0 ? -_delta_degrees : _delta_degrees;
				_next->SetDegrees(_degrees + delta);
				_next->SetDeactivate();
			}
		}

		_next->Spreading(_id);
	}

	if (_pre != NULL && _pre->_id != parent_id && _is_active && _pre->_id != 0)
	{
		int angle1 = _physical.vx_last > 0 ? _degrees : _pre->_degrees;
		int angle2 = _physical.vx_last > 0 ? _pre->_degrees : _degrees;

		if (angle1 > 270 && angle2 < 90)
		{
			angle2 += 360;
		}

		if (angle1 < 90 && angle2 > 270)
		{
			angle1 += 360;
		}

		if (angle1 - angle2 >= _delta_degrees)
		{
			int delta = _physical.vx_last > 0 ? -_delta_degrees : _delta_degrees;
			_pre->SetDegrees(_degrees + delta);
			_pre->SetActive();
			_pre->_physical.vx_last = _physical.vx_last;
		}

		_pre->Spreading(_id);
	}
}

void CBoss2Elbow::SetDegrees(int degrees)
{
	if (degrees < 0) _degrees = degrees + 360;
	if (degrees > 360) _degrees = degrees % 360;
}

void CBoss2Elbow::CalRadius(int degrees, int pre_degrees)
{
	int angle1 = _physical.vx_last > 0 ? _degrees : _pre->_degrees;
	int angle2 = _physical.vx_last > 0 ? _pre->_degrees : _degrees;

	if (angle1 > 270 && angle2 < 90)
	{
		angle2 += 360;
	}

	if (angle1 < 90 && angle2 > 270)
	{
		angle1 += 360;
	}

	int delta_degrees = abs(angle1 - angle2);
	delta_degrees = delta_degrees > _delta_degrees ? _delta_degrees : delta_degrees;

	float sina = sin(D3DXToRadian(delta_degrees));
	float delta = _radius * _radius - _pre->_delta_radius * _pre->_delta_radius * sina * sina;

	if (delta > 0)
	{
		float sqrt_delta = sqrt(delta);
		float x1 = _pre->_delta_radius * cos(D3DXToRadian(delta_degrees)) - sqrt_delta;
		float x2 = _pre->_delta_radius * cos(D3DXToRadian(delta_degrees)) + sqrt_delta;

		_delta_radius = x1 > x2 ? x1 : x2;
	}
	else if (delta == 0)
	{
		_delta_radius = _pre->_delta_radius * cos(D3DXToRadian(delta_degrees));
	}

	_delta_radius -= (_id - 1);
}

bool CBoss2Elbow::Boot(int time)
{
	D3DXVECTOR3 vector = D3DXVECTOR3(_x_circle - _physical.x, _y_circle - _physical.y, 0);
	int distance = sqrt(vector.x * vector.x + vector.y* vector.y);

	if (distance < _delta_radius)
	{
		_x_circle += _physical.vx * time;
		_y_circle += _physical.vy * time;
		return false;
	}

	return true;
}