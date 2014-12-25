#include "CNEBullet.h"

CNEBullet::CNEBullet(int id)
	:CBullet(id, BulletNE)
{
}

CNEBullet::~CNEBullet()
{
	CBullet::~CBullet();
}

void CNEBullet::LoadResources()
{
	CBullet::LoadResources();
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_bullet_sprite = new CSprite(rs->_bullet_ne);
	_current_sprite = _bullet_sprite;
}

void CNEBullet::Update(int delta_time)
{
	_physical.CalcPositionWithoutGravitation(delta_time);
	_physical.SetBounds(
		_physical.x,
		_physical.y,
		_current_sprite->sprite_texture->frame_width,
		_current_sprite->sprite_texture->frame_height);
}

void CNEBullet::Draw()
{
	if (_enable)
	{
		CCamera* c = CResourcesManager::GetInstance()->_camera;
		D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);
		_current_sprite->DrawWithDirection(pos, _physical.vx_last);

		if (_current_sprite == _ontarget_sprite)
		{
			_enable = false;
		}
	}

}

void CNEBullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}

void CNEBullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);
}