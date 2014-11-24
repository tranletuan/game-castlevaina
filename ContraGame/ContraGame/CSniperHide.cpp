#include "CSniperHide.h"

CSniperHide::CSniperHide(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 1;
	_last_time_shoot = 0;
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
	_current_sprite->index = 1;
}

void CSniperHide::Update(int delta_time)
{
	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	//Khi hp = 0 cho lính nhảy lên
	if (_hp == 0)
	{
		if (_physical.current_vy >= 0)
		{
			_physical.vx = 0.01f;
			_physical.vy = ENEMY_VY_DIE;
			_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
		}
		//Khi đạt độ cao cực đại thì trạng thái chuyển sang die
		else
		{
			SetStatus(EDie);
		}
	}
	else 
	{
		if (_is_shot && _queue_id_bullet.size() == 0)
		{
			_is_shot = false;
			_ready_shoot = false;
			_enemy_status = EWait;
			_physical.SetBounds(0, 0, 0, 0);

		}

		//Chờ bắn đợt đạn tiếp theo
		if (_enemy_status == EWait && CheckTarget())
		{
			if (_last_time_shoot == 0)
			{
				_last_time_shoot = GetTickCount();
			}

			DWORD now = GetTickCount();
			if (now - _last_time_shoot >= ENEMT_SNIPER_HIDE_TIME_WAIT)
			{
				SetStatus(EAttack);
				_physical.SetBounds(_physical.x, _physical.y, 20, 28);
				_last_time_shoot = 0;
			}
		}
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
	if (_hp == 0) return;
	if (!CheckTarget()) return; //Mục tiêu chưa vào tầm tấn công

	//Kiểm tra sprite bắn 
	if (_ready_shoot)
	{
		//Kiểm tra số đạn đã bắn
		if (_queue_id_bullet.size() < _max_bullet)
		{
			//Lấy góc bắn
			_attack_angle = _target_angle > 90 && _target_angle < 270 ? 180 : 0;
			_physical.vx_last = _target_angle > 90 && _target_angle < 270 ? -1 : 1;

			//Chỉnh tọa độ bắn
			int x = _physical.vx_last > 0 ? _physical.x + 13 : _physical.x - 13;
			int y = _physical.y + 6;

			int id = _weapon->ShootingBulletNE(D3DXVECTOR3(x, y, 0), _attack_angle, 0);

			if (id >= 0)
			{
				_queue_id_bullet.push(id);
				_is_shot = true;
			}
		}
	}
}

void CSniperHide::DrawWhenAttack(D3DXVECTOR3 pos)
{
	//Chạy hết frame mới bắn
	if (_hp != 0)
	{
		_ready_shoot = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 1, 3);
	}
	else
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last);
	}
}

void CSniperHide::DrawWhenWait(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 3, 5);
}

void CSniperHide::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _die_sprite;
	if (_current_sprite->index != _current_sprite->sprite_texture->count - 1)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 2);
	}
}

