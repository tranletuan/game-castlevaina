#include "CSniperBoss.h"

CSniperBoss::CSniperBoss(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 1;
	LoadResources();
}

CSniperBoss::~CSniperBoss()
{
}

void CSniperBoss::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	if (_specific_type == Sniper_Boss)
	{
		_live_sprite = new CSprite(rs->_enemy_sniper_boss);
		_die_sprite = new CSprite(rs->_effect_die);
		_current_sprite = _live_sprite;
		_max_bullet = ENEMY_SNIPER_BOSS_MAX_BULLET;
	}
}

void CSniperBoss::Update(int delta_time)
{
	//Target mục tiêu
	D3DXVECTOR3 pos_target = CResourcesManager::GetInstance()->m_posBill;
	SetTarget(pos_target.x, pos_target.y);

	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	//Khi hp = 0 cho lính nhảy lên
	if (_hp == 0)
	{
		_physical.SetBounds(0, 0, 0, 0);

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
		if (_is_shot && _queue_id_bullet.size() == 0 && _is_change)
		{
			_is_shot = false;
			_ready_shoot = false;
			_is_change = false;
			_enemy_status = EWait;
		}

		//Chờ bắn đợt đạn tiếp theo
		if (_enemy_status == EWait && CheckTarget())
		{
			if (_last_time_shoot == 0)
			{
				_last_time_shoot = GetTickCount();
			}

			DWORD now = GetTickCount();
			if (now - _last_time_shoot >= ENEMY_SNIPER_BOSS_TIME_WAIT)
			{
				SetStatus(EAttack);
				_last_time_shoot = 0;
			}
		}
	}

	switch (_enemy_status)
	{
	case EWait:
	case EDie:
		_physical.SetBounds(0, 0, 0, 0);
		_can_impact = false;
		if (_current_sprite == _die_sprite && _current_sprite->index == 2)
		{
			_enable = false;
		}
		break;
	case EAttack:
		if (_current_sprite->index > 1)
		{
			_can_impact = true;
			_physical.SetBounds(_physical.x, _physical.y, 15, 32);
		}
		break;
	}
}

void CSniperBoss::Draw()
{
	CEnemy::Draw();
}

void CSniperBoss::SetTarget(float x, float y)
{
	CEnemyUseGun::SetTarget(x, y);
	Attacking();
}

void CSniperBoss::Attacking()
{
	if (_hp == 0) return;
	if (!CheckTarget()) return; //Mục tiêu chưa vào tầm tấn công
	if (_is_change) return; //Cờ hiệu thay đổi trạng thái

	//Giãn cách bắn
	if (_last_time_shoot == 0)
	{
		_last_time_shoot = GetTickCount();
	}

	DWORD now = GetTickCount();

	//Giãn cách bắn 
	if (now - _last_time_shoot >= ENEMY_SNIPER_BOSS_ELAPSED_SHOOT && _ready_shoot)
	{
		//Kiểm tra số đạn đã bắn
		if (_queue_id_bullet.size() < _max_bullet)
		{
			//Lấy góc bắn
			//2 góc liền kề với góc của mục tiêu
			int angle_1 = _target_angle / ENEMY_ATTACK_DEGREES * ENEMY_ATTACK_DEGREES;
			int angle_2 = angle_1 + ENEMY_ATTACK_DEGREES;

			_attack_angle = (angle_2 - _target_angle) < (_target_angle - angle_1) ? angle_2 : angle_1;
			_attack_angle %= 360;
			_physical.vx_last = _attack_angle > 90 && _attack_angle < 270 ? -1 : 1;

			//Chỉnh tọa độ bắn
			int x = _physical.x;
			int y = _physical.y;

			x = _physical.vx_last > 0 ? x + 13 : x - 13;

			if (_attack_angle >= 0 && _attack_angle <= 180)
			{
				y += 8;
			}
			else
			{
				y -= 10;
			}

			int id = _weapon->ShootingBulletNE(D3DXVECTOR3(x, y, 0), _attack_angle, 0);

			if (id >= 0)
			{
				_queue_id_bullet.push(id);
				_is_shot = true;
				_is_shooting = true;
			}
		}
		else
		{
			_is_change = true;
		}

		_last_time_shoot = 0;
	}
}

void CSniperBoss::DrawWhenAttack(D3DXVECTOR3 pos)
{
	//Chạy hết frame mới bắn
	if (!_ready_shoot)
	{
		_ready_shoot = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 3);
	}
	else
	{
		if (_attack_angle >= 0 && _attack_angle <= 180)
		{
			if (_is_shooting)
			{
				_is_shooting = !_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 3, 4);
			}
			else
			{
				_current_sprite->DrawWithDirection(pos, _physical.vx_last, 3, 3);
			}
		}
		else
		{
			if (_is_shooting)
			{
				_is_shooting = !_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 5, 6);
			}
			else
			{
				_current_sprite->DrawWithDirection(pos, _physical.vx_last, 5, 5);
			}
		}
	}
}

void CSniperBoss::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _die_sprite;
	if (_current_sprite->index != _current_sprite->sprite_texture->count - 1)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 2);
	}
}

void CSniperBoss::DrawWhenWait(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 3, 0);
}
