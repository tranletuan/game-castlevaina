#include "CLBullet.h"

CLBullet::CLBullet(D3DXVECTOR3 pos, int angle, float direction, float v_max)
	:CBullet(pos, angle, direction, v_max)
{
	Moving(v_max);
	_scale.x = direction > 0 ? 1 : -1;
	_scale.y = 1;
}

CLBullet::~CLBullet()
{
	CBullet::~CBullet();
}

void CLBullet::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_current_sprite = new CSprite(rs->_bullet_l);
}

void CLBullet::Update(int delta_time)
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
	CCamera* c = CResourcesManager::GetInstance()->_camera;

	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);
	float angle = _physical.vx_last > 0 ? -_angle : _angle;
	_current_sprite->DrawTransform(pos.x, pos.y, _scale, angle, 0);
}

void CLBullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}

void CLBullet::Moving(float v)
{
	CalcVelocity(v);
}