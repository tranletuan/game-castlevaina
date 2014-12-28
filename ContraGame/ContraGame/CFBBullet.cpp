#include "CFBBullet.h"

CFBBullet::CFBBullet(int id)
	:CBullet(id, BulletFB)
{
}

CFBBullet::~CFBBullet()
{
}

void CFBBullet::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_bullet_sprite = new CSprite(rs->_bullet_f);
	_ontarget_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _bullet_sprite;
}

void CFBBullet::Update(int delta_time)
{
	if (_current_sprite == _bullet_sprite)
	{
		_physical.CalcPositionWithoutGravitation(delta_time);
		_physical.SetBounds(
			_physical.x,
			_physical.y,
			_current_sprite->sprite_texture->frame_width,
			_current_sprite->sprite_texture->frame_height);
	}
}

void CFBBullet::Draw()
{
	if (!_enable) return;

	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	if (_current_sprite == _bullet_sprite)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last);
	}
	else
	{
		_enable = !_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 2, 50);
	}
}

void CFBBullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);
	_hp = 1;
}

void CFBBullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}