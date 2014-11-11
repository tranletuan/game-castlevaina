#include "CNBullet.h"

CNBullet::CNBullet()
	: CBullet(BulletN)
{

}

CNBullet::~CNBullet()
{
	CBullet::~CBullet();
}

void CNBullet::LoadResources()
{
	CBullet::LoadResources();
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_bullet_sprite = new CSprite(rs->_bullet_n);
	_current_sprite = _bullet_sprite;
}

void CNBullet::Update(int delta_time)
{
	_physical.CalcPositionWithoutGravitation(delta_time);
	_physical.SetBounds(
		_physical.x,
		_physical.y,
		_current_sprite->sprite_texture->frame_width, 
		_current_sprite->sprite_texture->frame_height);
}

void CNBullet::Draw()
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

void CNBullet::Moving(float v_max)
{
	CalcVelocity(v_max);
}

void CNBullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}

void CNBullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);
}