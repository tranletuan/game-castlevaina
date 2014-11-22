#include "CMBullet.h"

CMBullet::CMBullet(int id)
	:CBullet(id, BulletM)
{

}

CMBullet::~CMBullet()
{
	CBullet::~CBullet();
}

void CMBullet::LoadResources()
{
	CBullet::LoadResources();
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_bullet_sprite = new CSprite(rs->_bullet_m);
	_current_sprite = _bullet_sprite;
}

void CMBullet::Update(float delta_time)
{
	_physical.CalcPositionWithoutGravitation(delta_time);
	_physical.SetBounds(
		_physical.x,
		_physical.y,
		_current_sprite->sprite_texture->frame_width,
		_current_sprite->sprite_texture->frame_height);
}

void CMBullet::Draw()
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

void CMBullet::Moving(float v_max)
{
	CalcVelocity(v_max);
}

void CMBullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}

void CMBullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);
}