#include "CFBullet.h"

CFBullet::CFBullet(int id) :CBullet(id, BulletF)
{

}

CFBullet::~CFBullet()
{
	CBullet::~CBullet();
}

void CFBullet::LoadResources()
{
	CBullet::LoadResources();
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_bullet_sprite = new CSprite(rs->_bullet_f);
	_current_sprite = _bullet_sprite;
}

void CFBullet::Update(int delta_time)
{
	//Cập nhật tâm quay
	_physical.CalcPositionWithoutGravitation(delta_time);
	_physical.SetBounds(
		_x_circle,
		_y_circle,
		_current_sprite->sprite_texture->frame_width,
		_current_sprite->sprite_texture->frame_height);

	//Tăng - giảm góc quay
	if (_physical.vx_last > 0)
	{
		_degrees -= BULLET_F_ELAPSED_DEGREES;
	}
	else
	{
		_degrees += BULLET_F_ELAPSED_DEGREES;
	}

	//Thiết lập để góc quay nằm trong khoảng 0 -> 360
	if (_degrees < 0) _degrees += 360;
	if (_degrees > 360) _degrees %= 360;

	//Tính toán góc quay
	_x_circle = _physical.x + BULLET_F_R * cos(D3DXToRadian(_degrees));
	_y_circle = _physical.y + BULLET_F_R * sin(D3DXToRadian(_degrees));

}

void CFBullet::Draw()
{
	if (_enable)
	{
		CCamera* c = CResourcesManager::GetInstance()->_camera;

		D3DXVECTOR3 pos = c->Transform(_x_circle, _y_circle);
		_current_sprite->DrawWithDirection(pos, _physical.vx_last);

		if (_current_sprite == _ontarget_sprite)
		{
			_enable = false;
		}
	}
}

void CFBullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}

void CFBullet::Moving(float v_max)
{
	CalcVelocity(v_max);
}

void CFBullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);

	_degrees = _physical.vx_last > 0 ? 180 : 0;
	_physical.x = _physical.vx_last > 0 ? pos.x + 20 : pos.x - 20;
}