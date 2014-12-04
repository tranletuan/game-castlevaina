#include "CWallTurret.h"

CWallTurret::CWallTurret(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 5;
	_attack_angle = 180;
	_real_angle = 180;
	_can_shoot = true;
	_physical.vx_last = -1;
	LoadResources();
}

CWallTurret::~CWallTurret()
{
}

void CWallTurret::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	_live_sprite = new CSprite(rs->_enemy_wall_turret);
	_die_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _live_sprite;
	_max_bullet = ENEMY_WALL_TURRET_MAX_BULLET;
}

void CWallTurret::Update(int delta_time)
{
	//Target mục tiêu
	D3DXVECTOR2 pos_target = CResourcesManager::GetInstance()->m_posBill;
	SetTarget(pos_target.x, pos_target.y);

	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	CCamera *_cam = CResourcesManager::GetInstance()->_camera;
	int levelMap = CResourcesManager::GetInstance()->m_levelMap;

	//chuyển state
	// Xét khoảng hoạt động của item stand the o level map
	switch (levelMap)
	{
	case 1:
	case 3:
		if (_physical.x + _current_sprite->sprite_texture->frame_width / 2 < _cam->getPosX() + _cam->getWidth() &&
			_physical.x - _current_sprite->sprite_texture->frame_width / 2 > _cam->getPosX())
		{
			_enemy_status = EAttack;
		}
		else
		{
			_enemy_status = EWait;
		}
		break;
	case 2:
		if (_physical.y + _current_sprite->sprite_texture->frame_height / 2 < _cam->getPosY()
			&& _physical.y - _current_sprite->sprite_texture->frame_height / 2 > 0)
		{
			_enemy_status = EAttack;
		}
		else
		{
			_enemy_status = EWait;
		}
		break;
	}

	if (_hp == 0)
	{
		SetStatus(EDie);
	}
}

void CWallTurret::Draw()
{
	CEnemy::Draw();
}

void CWallTurret::SetTarget(float x, float y)
{
	CEnemyUseGun::SetTarget(x, y);

	//Lấy góc bắn
	//2 góc liền kề với góc của mục tiêu
	int angle_1 = _target_angle / ENEMY_ATTACK_DEGREES * ENEMY_ATTACK_DEGREES;
	int angle_2 = angle_1 + ENEMY_ATTACK_DEGREES;

	//Tính góc bắn
	_attack_angle = (angle_2 - _target_angle) < (_target_angle - angle_1) ? angle_2 : angle_1;
	_attack_angle %= 360;

	//Xác định hướng súng
	_physical.vx_last = (_attack_angle >= 270 || _attack_angle <= 90) ? 1 : -1;

	_can_shoot = CheckCorrectAngle(); //Kiểm tra góc bắn và sprite hình có phù hợp hay chưa

	Attacking();
}

void CWallTurret::Attacking()
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
	if (now - _last_time_shoot >= ENEMY_WALL_TURRET_MAX_BULLET && _ready_shoot && _can_shoot)
	{
		//Kiểm tra số đạn đã bắn, nếu vẫn còn bắn được thì bắn
		if (_queue_id_bullet.size() < _max_bullet)
		{
			//Chỉnh tọa độ bắn
			ChangeShootPosition(_attack_angle);

			//Bắn
			int id = _weapon->ShootingBulletNE(D3DXVECTOR3(_x_shoot, _y_shoot, 0), _attack_angle, 0);

			if (id >= 0)
			{
				_queue_id_bullet.push(id);
			}

			_last_time_shoot = now;
		}
	}

}

void CWallTurret::DrawWhenAttack(D3DXVECTOR3 pos)
{
	if (!_ready_shoot)
	{
		_ready_shoot = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 5, 20);
	}
	else
	{
		int start = GetIndexSpriteByAngle(_real_angle);
		int end = start + 2;

		//Nếu góc bắn chưa đúng
		if (!_can_shoot)
		{
			bool done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, start, end, 250);
			if (done) ChangeRealAngle();
		}
		//Góc bắn đã chính xác
		else
		{
			_current_sprite->DrawWithDirection(pos, 1, start, end);
		}
	}
}

void CWallTurret::DrawWhenWait(D3DXVECTOR3 pos)
{
	if (_ready_shoot)
	{
		_ready_shoot = !_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 5, 0, 20);
	}
	else
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 2);
	}
}

void CWallTurret::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _die_sprite;
	if (_current_sprite->index != 2)
	{
		_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 2);
	}
	else
	{
		_enable = false;
	}
}

bool CWallTurret::CheckCorrectAngle()
{
	//Kiểm tra góc bắn có phù hợp với sprite hình hay chưa
	return (_attack_angle == _real_angle);
}

int CWallTurret::GetIndexSpriteByAngle(int angle)
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
	case 90:
		index = 15;
		break;
	case 60:
		index = 18;
		break;
	case 30:
		index = 21;
		break;
	case 0:
		index = 24;
		break;
	case 330:
		index = 27;
		break;
	case 300:
		index = 30;
		break;
	case 270:
		index = 33;
		break;
	case 240:
		index = 36;
		break;
	case 210:
		index = 39;
		break;
	}

	return index;
}

void CWallTurret::ChangeRealAngle()
{
	int angle_1 = _real_angle < 180 ? _real_angle : _real_angle - 180;
	int angle_2 = _real_angle < 180 ? _real_angle + 180 : _real_angle;

	//Góc bắn nằm bên phải đường thẳng bờ đi qua tâm quay và góc hiện tại
	if (_attack_angle >= angle_1 && _attack_angle <= angle_2)
	{
		if (_real_angle < 180)
		{
			_real_angle += ENEMY_ATTACK_DEGREES;
		}
		else
		{
			_real_angle -= ENEMY_ATTACK_DEGREES;
		}
	}
	else
	{
		if (_real_angle < 180)
		{
			_real_angle -= ENEMY_ATTACK_DEGREES;
		}
		else
		{
			_real_angle += ENEMY_ATTACK_DEGREES;
		}
	}

	//Quy định tăng giảm chỉ nằm trong khoảng 0->359
	if (_real_angle >= 360) _real_angle %= 360;
	if (_real_angle < 0) _real_angle += 360;	
}

void CWallTurret::ChangeShootPosition(int angle)
{
	_x_shoot = _physical.x;
	_y_shoot = _physical.y;

	switch (angle)
	{
	case 0:
		_x_shoot += 16;
		break;
	case 30:
		_x_shoot += 12;
		_y_shoot += 6;
		break;
	case 60:
		_x_shoot += 6;
		_y_shoot += 12;
		break;
	case 90:
		_y_shoot += 16;
		break;
	case 120:
		_x_shoot -= 6;
		_y_shoot += 12;
		break;
	case 150:
		_x_shoot -= 12;
		_y_shoot += 6;
		break;
	case 180: 
		_x_shoot -= 16;
		break;
	case 210:
		_x_shoot -= 12;
		_y_shoot -= 6;
		break;
	case 240:
		_x_shoot -= 6;
		_y_shoot -= 12;
		break;
	case 270:
		_y_shoot -= 16;
		break;
	case 300: 
		_x_shoot += 6;
		_y_shoot -= 12;
		break;
	case 330:
		_x_shoot += 12;
		_y_shoot -= 6;
		break;
	}
}