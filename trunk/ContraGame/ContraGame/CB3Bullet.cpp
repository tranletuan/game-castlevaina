#include "CB3Bullet.h"

CB3Bullet::CB3Bullet(int id)
	:CBullet(id, BulletB3)
{
}

CB3Bullet::~CB3Bullet()
{
}

void CB3Bullet::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_bullet_sprite = new CSprite(rs->_bullet_b3);
	_ontarget_sprite = new CSprite(rs->_effect_die);
	_current_sprite = _bullet_sprite;
}

void CB3Bullet::Update(int delta_time)
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos_view = c->Transform(_physical.x, _physical.y);

	//Kiểm tra khoảng cách đạn rơi
	if ((pos_view.x - 12 < 0 || pos_view.x + 12 > c->getWidth() ||
		abs(_x_shoot - _physical.x) >= BULLET_B3_DISTANCE_FALL) && !_is_fall)
	{
		_is_fall = true;
		_physical.vx_last = _physical.vx;
		_physical.vx = 0;
		_physical.vy = -BULLET_B3_V;
	}

	_physical.CalcPositionWithoutGravitation(delta_time);
	_physical.SetBounds(
		_physical.x,
		_physical.y,
		10,
		10);
}

void CB3Bullet::Draw()
{
	if (!_enable) return;
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	if (_current_sprite == _bullet_sprite)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 2, 50);
	}
	else
	{
		_enable = !_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 2, 50);
	}
}

void CB3Bullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);
	_x_shoot = pos.x;
	_is_fall = false;
	_hp = 1;
}

void CB3Bullet::CalcVelocity(float v_max)
{
	CBullet::CalcVelocity(v_max);
}