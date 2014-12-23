#include "CSniperWater.h"

CSniperWater::CSniperWater(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 1;
	_last_time_shoot = 0;
	LoadResources();
}

CSniperWater::~CSniperWater()
{
}

void CSniperWater::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	if (_specific_type == Sniper_Water)
	{
		_live_sprite = new CSprite(rs->_enemy_sniper_water);
		_die_sprite = new CSprite(rs->_effect_die);
		_current_sprite = _live_sprite;
		_max_bullet = ENEMY_SNIPER_WATER_MAX_BULLET;
	}
}

void CSniperWater::Draw()
{
	CEnemy::Draw();
}

void CSniperWater::Update(int delta_time)
{
	//Target mục tiêu
	D3DXVECTOR2 pos_target = CResourcesManager::GetInstance()->m_posBill;
	SetTarget(pos_target.x, pos_target.y);

	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	//Khi hp = 0 cho lính nhảy lên
	if (_hp == 0)
	{
		SetStatus(EDie);
	}
	else
	{
		//Khi đã bắn ra 1 viên đạn và viên đạn hết hiệu lực thì trở về trạng thái chờ
		if (_is_shot && _queue_id_bullet.size() == 0)
		{
			_is_shot = false;
			_enemy_status = EWait;

		}

		//Chờ bắn đợt đạn tiếp theo
		if (_enemy_status == EWait)
		{
			if (_last_time_shoot == 0)
			{
				_last_time_shoot = GetTickCount();
			}

			DWORD now = GetTickCount();
			if (now - _last_time_shoot >= ENEMY_SNIPER_WATER_TIME_WAIT)
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
			_can_impact = true;
			_physical.SetBounds(_physical.x, _physical.y, 15, 32);
		break;
	}
}

void CSniperWater::SetTarget(float x, float y)
{
	_target.x = x;
	_target.y = y;

	if (_target.y >= _physical.y)
	{
		_attack_angle = 90;
		SetWeapon(CResourcesManager::GetInstance()->_weapon_enemy);
		Attacking();
	}
}

void CSniperWater::Attacking()
{
	if (_hp == 0) return;
	if (_enemy_status != EAttack) return;
	if (_weapon == NULL) return;

	//Kiểm tra số đạn đã bắn
	if (_queue_id_bullet.size() == 0)
	{
		//Chỉnh tọa độ bắn
		int x = _physical.x + 4;
		int y = _physical.y + 10;

		int id = _weapon->ShootingBulletNE(D3DXVECTOR3(x, y, 0), _attack_angle, 0);

		if (id >= 0)
		{
			_queue_id_bullet.push(id);
			_is_shot = true;
		}
	}
}

void CSniperWater::DrawWhenAttack(D3DXVECTOR3 pos)
{
	if (_hp > 0)
	{
		_current_sprite->SelectFrameOf(0);
		_current_sprite->Draw(pos.x, pos.y);
	}
}

void CSniperWater::DrawWhenWait(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirection(pos, 1, 1, 2, 300);
}

void CSniperWater::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _die_sprite;
	if (_current_sprite->index != _current_sprite->sprite_texture->count - 1)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 2);
	}
}


