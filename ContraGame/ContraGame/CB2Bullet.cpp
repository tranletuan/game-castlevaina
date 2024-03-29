#include "CB2Bullet.h"

CB2Bullet::CB2Bullet(int id)
	:CBullet(id, BulletB2)
{
}

CB2Bullet::~CB2Bullet()
{
	CBullet::~CBullet();
}

void CB2Bullet::LoadResources()
{
	CBullet::LoadResources();
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_bullet_sprite = new CSprite(rs->_bullet_b2);
	_ontarget_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _bullet_sprite;
}

void CB2Bullet::Update(int delta_time)
{
	_physical.CalcPositionWithoutGravitation(delta_time);
	_physical.SetBounds(
		_physical.x,
		_physical.y,
		_current_sprite->sprite_texture->frame_width - 2,
		_current_sprite->sprite_texture->frame_height - 2);
}

void CB2Bullet::Draw()
{
	if (_enable)
	{
		CCamera* c = CResourcesManager::GetInstance()->_camera;
		D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

		if (_current_sprite == _bullet_sprite)
		{
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 3, 200);
		}
		else
		{
			_enable = !_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 2, 50);
		}
	}

}

void CB2Bullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}

void CB2Bullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);
}