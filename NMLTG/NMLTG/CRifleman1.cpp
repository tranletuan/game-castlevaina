#include "CRifleman1.h"

CRifleman1::CRifleman1(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 1;
	Moving(0);
}

CRifleman1::~CRifleman1()
{
	
}

void CRifleman1::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	if (_specific_type == Rifleman1)
	{
		_live_sprite = new CSprite(rs->_enemy_rifleman_1);
		_max_bullet = ENEMY_RIFLEMAN_MAX_BULLET;
	}
	
	_die_sprite = new CSprite(rs->_effect_die);
	_current_sprite = _live_sprite;
}

void CRifleman1::Update(int delta_time)
{
	//Khi hp = 0 cho lính nhảy lên
	if (_hp == 0 && _physical.current_vy >= 0)
	{
		_physical.vx = 0;
		_physical.vy = ENEMY_VY_DIE;
		_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
	}

	//Khi đạt độ cao cực đại thì trạng thái chuyển sang die
	if (_physical.current_vy < 0)
	{
		SetStatus(EDie);
	}
}

void CRifleman1::Draw()
{
	CEnemy::Draw();
}

void CRifleman1::Attacking(CEnemyWeapon* weapon)
{
	if (!CheckTarget()) return; //Mục tiêu chưa vào tầm tấn công
	
	DWORD now = GetTickCount();

	//Giãn cách bắn 
	if (now - _last_time_shoot >= ENEMY_RIFLEMAN_ELAPSED_SHOOT)
	{
		//Cập nhật lại những viên đạn có thể bắn trong list của enemy
		weapon->UpdateQueueIdBullet(_queue_id_bullet);

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
			int id = weapon->ShootingBulletNE(D3DXVECTOR3(x, y, 0), _attack_angle, 0);
			
			if (id >= 0)
			{
				_queue_id_bullet.push(id);
			}

			_last_time_shoot = now;
			SetStatus(EAttack);
		}
	}
}

void CRifleman1::DrawWhenAttack(D3DXVECTOR3 pos)
{
	bool done = true;
	if (_attack_angle == 180 || _attack_angle == 0)
	{
		done  = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 1, 2);
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

void CRifleman1::DrawWhenWait(D3DXVECTOR3 pos)
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

void CRifleman1::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _die_sprite;
	if (_current_sprite->index != _current_sprite->sprite_texture->count - 1)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 2);
	}
}

void CRifleman1::Moving(float vx)
{
	_physical.vx = vx;
}
