#include "CSBullet.h"

CSBullet::CSBullet(int id)
	:CBullet(id, BulletS)
{
}

CSBullet::~CSBullet()
{
	CBullet::~CBullet();
}

void CSBullet::LoadResources()
{
	CBullet::LoadResources();
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_bullet_sprite = new CSprite(rs->_bullet_s);
	_current_sprite = _bullet_sprite;
}

void CSBullet::Update(int delta_time)
{
	_physical.CalcPositionWithoutGravitation(delta_time);
	_physical.SetBounds(
		_physical.x,
		_physical.y,
		_current_sprite->sprite_texture->frame_width,
		_current_sprite->sprite_texture->frame_height);
}

void CSBullet::Draw()
{
	if (_enable)
	{
		CCamera* c = CResourcesManager::GetInstance()->_camera;
		D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

		if (_current_sprite == _bullet_sprite)
		{
			_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 2, BULLET_S_ELAPSED_TIME);
		}
		else
		{
			_current_sprite->Draw(pos.x, pos.y);
			_enable = false;
		}
	}
}

void CSBullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}

void CSBullet::Moving(float v_max)
{
	CalcVelocity(v_max);
}

void CSBullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);
}