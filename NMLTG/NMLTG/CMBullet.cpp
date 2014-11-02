#include "CMBullet.h"

CMBullet::CMBullet(D3DXVECTOR3 pos, int angle, float v_max, float vo)
	:CBullet(BulletM, pos, angle, v_max, vo)
{
	Moving(v_max);
}

CMBullet::~CMBullet()
{
	CBullet::~CBullet();
}

void CMBullet::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_current_sprite = new CSprite(rs->_bullet_m);
}

void CMBullet::Update(int delta_time)
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
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	_current_sprite->DrawWithDirecion(pos, _physical.vx_last);
}

void CMBullet::Moving(float v_max)
{
	CalcVelocity(v_max);
}

void CMBullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}