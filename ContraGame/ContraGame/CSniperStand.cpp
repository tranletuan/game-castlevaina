#include "CSniperStand.h"

CSniperStand::CSniperStand(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width - 8, height)
{
	_hp = 1;
	_can_impact = true;
	LoadResources();
}

CSniperStand::~CSniperStand()
{
}

void CSniperStand::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	if (_specific_type == Sniper_Stand)
	{
		_live_sprite = new CSprite(rs->_enemy_sniper_stand);
		_die_sprite = new CSprite(rs->_effect_die);
		_current_sprite = _live_sprite;
		_max_bullet = ENEMY_SNIPER_STAND_MAX_BULLET;
	}
}

void CSniperStand::Update(int delta_time)
{
	//Target mục tiêu
	D3DXVECTOR3 pos_target = CResourcesManager::GetInstance()->m_posBill;
	SetTarget(pos_target.x, pos_target.y);

	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	//Khi hp = 0 cho lính nhảy lên
	if (_hp == 0 && _physical.current_vy >= 0)
	{
		_physical.SetBounds(0, 0, 0, 0);
		_physical.vx = 0.01f;
		_physical.vy = ENEMY_VY_DIE;
		_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
	}

	//Khi đạt độ cao cực đại thì trạng thái chuyển sang die
	if (_physical.current_vy < 0)
	{
		SetStatus(EDie);
	}
}

void CSniperStand::Draw()
{
	CEnemy::Draw();
}

void CSniperStand::SetTarget(float x, float y)
{
	CEnemyUseGun::SetTarget(x, y);
	Attacking();
}

void CSniperStand::Attacking()
{
	if (_hp == 0) return;
	if (!CheckTarget()) return; //Mục tiêu chưa vào tầm tấn công

	DWORD now = GetTickCount();

	//Giãn cách bắn 
	if (now - _last_time_shoot >= ENEMY_SNIPER_STAND_ELAPSED_SHOOT)
	{
		//Kiểm tra số đạn đã bắn, nếu vẫn còn bắn được thì bắn
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

			//Điều chỉnh đạn bay ra hợp lý với sprite hình
			if (_attack_angle == 180 || _attack_angle == 0)
			{
				y = y + 8;
			}
			else if (_attack_angle < 180)
			{
				y = y + 20;
			}
			else
			{
				y = y - 10;
			}

			//Bắn
			int id = _weapon->ShootingBulletNE(D3DXVECTOR3(x, y, 0), _attack_angle, 0);

			if (id >= 0)
			{
				_queue_id_bullet.push(id);
			}

			_last_time_shoot = now;
			SetStatus(EAttack);
		}
	}
}

void CSniperStand::DrawWhenAttack(D3DXVECTOR3 pos)
{
	bool done = true;
	if (_attack_angle == 180 || _attack_angle == 0)
	{
		done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 1, 2);
	}
	else if (_attack_angle > 0 && _attack_angle < 180)
	{
		done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 3, 4);
	}
	else
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last);
	}

	if (done == true)
	{
		_enemy_status = EWait;
	}
}

void CSniperStand::DrawWhenWait(D3DXVECTOR3 pos)
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

void CSniperStand::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _die_sprite;
	if (_current_sprite->index != _current_sprite->sprite_texture->count - 1)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 2);
	}
	else
	{
		_enable = false;
	}
}

