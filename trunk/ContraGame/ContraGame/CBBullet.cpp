#include "CBBullet.h"

CBBullet::CBBullet(int id)
	:CBullet(id, BulletB)
{
}

CBBullet::~CBBullet()
{
	CBullet::~CBullet();
}

void CBBullet::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_ontarget_sprite = new CSprite(rs->_effect_destroy);
	_bullet_sprite = new CSprite(rs->_bullet_b);
	_current_sprite = _bullet_sprite;
}

void CBBullet::Update(int delta_time)
{
	if (_current_sprite == _bullet_sprite)
	{
		_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
		_physical.SetBounds(
			_physical.x,
			_physical.y,
			_current_sprite->sprite_texture->frame_width,
			_current_sprite->sprite_texture->frame_height);
	}
}

void CBBullet::Draw()
{
	if (_enable)
	{
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
}

void CBBullet::CalcVelocity(float v_max)
{
	_physical.vx = rand() % BULLET_B_RANDOM_VX / 1000.0f + v_max;
	_physical.vx *= _physical.vx_last;
	_physical.vy = BULLET_B_VY;
}

void CBBullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);
	_physical.time_in_space = GetTickCount();
}