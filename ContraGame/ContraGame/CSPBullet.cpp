#include "CSPBullet.h"

CSPBullet::CSPBullet(int id)
	:CBullet(id, BulletSP)
{
}

CSPBullet::~CSPBullet()
{
}

void CSPBullet::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_bullet_sprite = new CSprite(rs->_bullet_sp);
	_ontarget_sprite = new CSprite(rs->_effect_die);
	_split_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _bullet_sprite;
	_max_altitude = 100;
}

void CSPBullet::Update(int delta_time)
{
	if (!_enable) return;
	
	//Đạt độ cao nhất định thì đạn sẽ chuyển hướng
	if (_physical.y - _y_shoot >= _max_altitude && !_is_split)
	{
		_is_split = true;
	}

	if (!_is_split)
	{
		_physical.vx = 0;
		_physical.vy = BULLET_SP_VY;
		_physical.CalcPositionWithoutGravitation(delta_time);
	}
	else if (_physical.n == 0)
	{
		_physical.vx = _vx_split;
		_physical.vy = 4.5f;
		_physical.CalcPositionWithGravitation(delta_time, 0.008f);
	}

	_physical.SetBounds(
		_physical.x,
		_physical.y,
		_current_sprite->sprite_texture->frame_width,
		_current_sprite->sprite_texture->frame_height);
}

void CSPBullet::Draw()
{
	if (!_enable) return;
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	//Vẽ đạn
	if (_current_sprite == _bullet_sprite)
	{
		_current_sprite->Draw(pos.x, pos.y);
	}
	else if (_current_sprite == _ontarget_sprite)
	{
		_enable = !_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 2, 50);
	}

	//Vẽ hiệu ứng chuyển hướng
	if (_is_split && _split_sprite->index != 2 && _vx_split == 0)
	{
		D3DXVECTOR3 pos_split = c->Transform(_pos_split.x, _pos_split.y);
		_split_sprite->DrawWithDirectionAndOneTimeEffect(pos_split, 1, 0, 2);
	}
}

void CSPBullet::Shoot(D3DXVECTOR3 pos, int angle, float v_max, float vo)
{
	CBullet::Shoot(pos, angle, v_max, vo);
	_physical.time_in_space = 0;
	_pos_split.x = pos.x;
	_pos_split.y = pos.y + _max_altitude;
	_is_split = false;
	_y_shoot = pos.y;
	_split_sprite->Reset();
}

void CSPBullet::CalcVelocity(float v_max)
{
	_vx_split = 0;
	if (_angle > 90 && _angle < 180) _vx_split = -v_max;
	if (_angle < 90 && _angle > 0) _vx_split = v_max;
}