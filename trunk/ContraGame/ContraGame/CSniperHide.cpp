#include "CSniperHide.h"

CSniperHide::CSniperHide(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 1;
	LoadResources();
}

CSniperHide::~CSniperHide()
{
	delete _live_sprite;
	delete _die_sprite;
}

void CSniperHide::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	if (_specific_type == Sniper_Hide)
	{
		_live_sprite = new CSprite(rs->_enemy_sniper_hide);
		_max_bullet = ENEMY_SNIPER_HIDE_MAX_BULLET;
	}

	_die_sprite = new CSprite(rs->_effect_die);
	_current_sprite = _live_sprite;
}

void CSniperHide::Update(int delta_time)
{
	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	//Khi hp = 0 cho lính nhảy lên
	if (_hp == 0 && _physical.current_vy >= 0)
	{
		_physical.vx = 0.01f;
		_physical.vy = ENEMY_VY_DIE;
		_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
	}

	//Khi đạt độ cao cực đại thì trạng thái chuyển sang die
	if (_physical.current_vy < 0)
	{
		SetStatus(EDie);
	}

	DWORD now = GetTickCount();
	if (now - _last_time_shoot >= ENEMT_SNIPER_HIDE_TIME_WAIT)
	{
		SetStatus(EAttack);
	}
}

void CSniperHide::Draw()
{
	CEnemy::Draw();
}

void CSniperHide::SetTarget(float x, float y)
{
	CEnemyUseGun::SetTarget(x, y);
	Attacking();
}

void CSniperHide::Attacking()
{
	if (!CheckTarget()) return; //Mục tiêu chưa vào tầm tấn công

	//Kiểm tra sprite bắn 
	if (_shoot_done)
	{
		//Kiểm tra số đạn đã bắn, nếu vẫn còn bắn được thì bắn
		if (_queue_id_bullet.size() < _max_bullet)
		{
			//Lấy góc bắn
			_attack_angle = _target_angle > 90 && _target_angle < 270 ? 180 : 0;
			_physical.vx_last = _target_angle > 90 && _target_angle < 270 ? -1 : 1;

			//Chỉnh tọa độ bắn
			int x = _physical.vx_last > 0 ? _physical.x + 13 : _physical.x - 13;
			int y = _physical.y;

			int id = _weapon->ShootingBulletNE(D3DXVECTOR3(x, y, 0), _attack_angle, 0);

			if (id >= 0)
			{
				_queue_id_bullet.push(id);
			}

			_shoot_done = false;
		}
	}
}

void CSniperHide::DrawWhenAttack(D3DXVECTOR3 pos)
{
	_shoot_done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 1, 3);
}

void CSniperHide::DrawWhenWait(D3DXVECTOR3 pos)
{
	if (_attack_angle == 180 || _attack_angle == 0)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 1, 1);
	}
	else if (_attack_angle > 0 && _attack_angle < 180)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 3, 3);
	}
	else
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last);
	}
}

void CSniperHide::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _die_sprite;
	if (_current_sprite->index != _current_sprite->sprite_texture->count - 1)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 2);
	}
}

