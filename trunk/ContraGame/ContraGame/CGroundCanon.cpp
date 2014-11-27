#include "CGroundCanon.h"

CGroundCanon::CGroundCanon(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 5;
	_attack_angle = 180;
	_real_angle = 180;
	_can_shoot = true;
	_physical.vx_last = -1;
	LoadResources();
}

CGroundCanon::~CGroundCanon()
{
}

void CGroundCanon::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	_live_sprite = new CSprite(rs->_enemy_ground_canon);
	_die_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _live_sprite;
	_max_bullet = ENEMY_GROUND_CANON_MAX_BULLET;
}

void CGroundCanon::Update(int delta_time)
{
	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	if (_hp == 0)
	{
		SetStatus(EDie);
	}
}

void CGroundCanon::Draw()
{
	CEnemy::Draw();
}

void CGroundCanon::SetTarget(float x, float y)
{
	CEnemyUseGun::SetTarget(x, y);

	//Lấy góc bắn
	//2 góc liền kề với góc của mục tiêu
	int angle_1 = _target_angle / ENEMY_ATTACK_DEGREES * ENEMY_ATTACK_DEGREES;
	int angle_2 = angle_1 + ENEMY_ATTACK_DEGREES;

	_attack_angle = (angle_2 - _target_angle) < (_target_angle - angle_1) ? angle_2 : angle_1;
	_attack_angle %= 360;
	_can_shoot = CheckCorrectAngle(); //Kiểm tra góc bắn và sprite hình có phù hợp hay chưa

	Attacking();
}

void CGroundCanon::Attacking()
{
	if (_hp == 0) return;
	
	if (!CheckTarget())
	{
		_enemy_status = EWait;
		return;
	}

	SetStatus(EAttack);
	DWORD now = GetTickCount();

	//Giãn cách bắn 
	if (now - _last_time_shoot >= ENEMY_GROUND_CANON_ELAPSED_SHOOT && _ready_shoot)
	{
		int test = _queue_id_bullet.size();
		//Kiểm tra số đạn đã bắn, nếu vẫn còn bắn được thì bắn
		if (_queue_id_bullet.size() < _max_bullet)
		{
			//Chỉnh tọa độ bắn
			int x = _physical.x - 18;
			int y = _physical.y + 9;

			if (_real_angle == 180)
			{
				y += -10;
			} 
			else if (_real_angle <= 120)
			{
				x += 10;
				y += 4;
			}

			if (_can_shoot && _attack_angle <= 180 && _attack_angle >= 120)
			{
				//Bắn
				int id = _weapon->ShootingBulletNE(D3DXVECTOR3(x, y, 0), _attack_angle, 0);

				if (id >= 0)
				{
					_queue_id_bullet.push(id);
				}
			}

			_last_time_shoot = now;
		}
	}

}

void CGroundCanon::DrawWhenAttack(D3DXVECTOR3 pos)
{
	if (!_ready_shoot)
	{
		_ready_shoot = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 6, 20);
	}
	else
	{
		int start = GetIndexSpriteByAngle(_real_angle);

		if (!_can_shoot && _attack_angle <= 180 && _attack_angle >= 120)
		{
			int end = GetIndexSpriteByAngle(_attack_angle);
			_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, start, end, 100, 3);
		}
		else 
		{
			int end = start + 2;
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, start, end);
		}
	}
}

void CGroundCanon::DrawWhenWait(D3DXVECTOR3 pos)
{
	if (_ready_shoot)
	{
		_ready_shoot = !_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 5, 0, 20);
	}
}

void CGroundCanon::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _die_sprite;
	if (_current_sprite->index != 2)
	{
		_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 2);
	}
}

bool CGroundCanon::CheckCorrectAngle()
{
	//Kiểm tra góc bắn có phù hợp với sprite hình hay chưa
	switch (_current_sprite->index)
	{
	case 6:
	case 7:
	case 8:
		_real_angle = 180;
		break;
	case 9:
	case 10:
	case 11:
		_real_angle = 150;
		break;
	case 12:
	case 13:
	case 14:
		_real_angle = 120;
		break;
	}

	return (_attack_angle == _real_angle);
}

int CGroundCanon::GetIndexSpriteByAngle(int angle)
{
	int index = _current_sprite->index;
	switch (angle)
	{
	case 180:
		index = 6;
		break;
	case 150:
		index = 9;
		break;
	case 120:
		index = 12;
		break;
	}

	return index;
}