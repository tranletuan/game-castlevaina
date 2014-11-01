#include "CSBullet.h"

CSBullet::CSBullet(D3DXVECTOR3 pos, int angle, float v_max, float vo)
	:CBullet(pos, angle, v_max, vo)
{
	Moving(v_max);
}

CSBullet::~CSBullet()
{
	CBullet::~CBullet();
}

void CSBullet::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_current_sprite = new CSprite(rs->_bullet_s, BULLET_S_ELAPSED_TIME);
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
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	if (_current_sprite->index < _current_sprite->end)
	{
		_current_sprite->UpdateEffect();
	}

	if (_physical.vx_last > 0)
	{
		_current_sprite->Draw(pos.x, pos.y);
	}
	else
	{
		_current_sprite->DrawFlipY(pos.x, pos.y);
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