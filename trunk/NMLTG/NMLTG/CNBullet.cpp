#include "CNBullet.h"

CNBullet::CNBullet(D3DXVECTOR3 pos, int angle, float v_max, float vo)
	: CBullet(BulletN, pos, angle, v_max, vo)
{
	Moving(v_max);
}

CNBullet::~CNBullet()
{
	CBullet::~CBullet();
}

void CNBullet::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_current_sprite = new CSprite(rs->_bullet_n);
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
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	_current_sprite->DrawWithDirecion(pos, _physical.vx_last);
}

void CNBullet::Moving(float v_max)
{
	CalcVelocity(v_max);
}

void CNBullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}