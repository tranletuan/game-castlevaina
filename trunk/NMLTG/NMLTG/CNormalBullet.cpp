#include "CNormalBullet.h"

CNormalBullet::CNormalBullet(D3DXVECTOR3 pos, int angle, float direction) 
	: CBullet(pos, angle, direction)
{
	Moving(BULLET_V);
}

CNormalBullet::~CNormalBullet()
{
	if (_current_sprite != NULL)
	{
		delete _current_sprite;
	}
}

void CNormalBullet::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_current_sprite = new CSprite(rs->_nbullet);
}

void CNormalBullet::Update(int delta_time)
{
	_physical.CalcPositionWithoutGravitation(delta_time);
}

void CNormalBullet::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	_current_sprite->DrawWithDirecion(pos, _physical.vx_last);
}

void CNormalBullet::Moving(float v)
{
	CalcVelocity(v);
}