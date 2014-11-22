#include "CLBullet.h"

CLBullet::CLBullet(int id) :CBullet(id, BulletL)
{

}

CLBullet::~CLBullet()
{
	CBullet::~CBullet();
}

void CLBullet::LoadResources()
{
	CBullet::LoadResources();
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_bullet_sprite = new CSprite(rs->_bullet_l);
	_current_sprite = _bullet_sprite;
}

void CLBullet::Update(float delta_time)
{
	_physical.CalcPositionWithoutGravitation(delta_time);
	_physical.SetBounds(
		_physical.x,
		_physical.y,
		_current_sprite->sprite_texture->frame_width,
		_current_sprite->sprite_texture->frame_width);
}

void CLBullet::Draw()
{
	if (_enable)
	{
		CCamera* c = CResourcesManager::GetInstance()->_camera;

		D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);
		_current_sprite->DrawTransform(pos.x, pos.y, _scale, 360 - _angle, 0);

		if (_current_sprite == _ontarget_sprite)
		{
			_enable = false;
		}
	}
}

void CLBullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}

void CLBullet::Moving(float v_max)
{
	CalcVelocity(v_max);
}

void CLBullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);
	_scale.x = _physical.vx_last > 0 ? 1 : -1;
	_scale.y = 1;
}