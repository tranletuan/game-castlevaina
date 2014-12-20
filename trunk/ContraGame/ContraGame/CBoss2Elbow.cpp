#include "CBoss2Elbow.h"

CBoss2Elbow::CBoss2Elbow(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	: CObject(id, specific_type, Enemy, pos, width, height)
{
	_hp = 1;
	_is_active = true;
	LoadResources();
}

CBoss2Elbow::~CBoss2Elbow()
{
}

void CBoss2Elbow::LoadResources()
{
	if (_specific_type == Boss2_Elbow)
	{
		CResourcesManager* rs = CResourcesManager::GetInstance();
		_live_sprite = new CSprite(rs->_boss2_elbow);
		_die_sprite = new CSprite(rs->_effect_destroy);
		_current_sprite = _live_sprite;
		_radius = _id * (rs->_boss2_elbow->frame_width - 4);
		if (_radius != 0)
		{
			_delta_degrees = D3DXToDegree(acos(1 - BOSS2_DISTANCE_CHANGE * BOSS2_DISTANCE_CHANGE / (float)(2 * _radius* _radius)));
		}
	}
}

void CBoss2Elbow::Update(int time)
{
	if (_hp > 0 && _is_active)
	{
		Turning();
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

	//Tính toán góc quay
	_x_circle = _physical.x + _radius * cos(D3DXToRadian(_degrees));
	_y_circle = _physical.y + _radius * sin(D3DXToRadian(_degrees));
	_physical.SetBounds(
		_x_circle, 
		_y_circle, 
		_current_sprite->sprite_texture->frame_width, 
		_current_sprite->sprite_texture->frame_height);
}

void CBoss2Elbow::SetDeactivate()
{
	_is_active = false;
}

void CBoss2Elbow::SetActive()
{
	_is_active = true;
	_last_degrees = _degrees;
}

void CBoss2Elbow::Spreading(int parent_id)
{
	if (_delta_degrees <= 0) return;
	if (_next != NULL) _next->_physical.vx_last = _physical.vx_last;
	if (_pre != NULL) _pre->_physical.vx_last = _physical.vx_last;

	if (_next != NULL && _next->_id != parent_id)
	{
		if (!_next->_is_active)
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
				/*int delta = _physical.vx_last > 0 ? -_delta_degrees : _delta_degrees;
				_next->SetDegrees(_degrees + delta);*/
				_next->SetActive();
			}
		}

		_next->Spreading(_id);
	}

	if (_pre != NULL && _pre->_id != parent_id)
	{
		if (!_pre->_is_active)
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
				_pre->SetActive();
			}
		}

		_pre->Spreading(_id);
	}
}

void CBoss2Elbow::SetDegrees(int degrees)
{
	if (degrees < 0) _degrees = degrees + 360;
	if (degrees > 360) _degrees = degrees % 360;
}