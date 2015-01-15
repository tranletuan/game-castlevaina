#include "CTank.h"

CTank::CTank(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 30;
	_can_impact = true;
	_distance_move = 4.5;
	_count = 0;
	_attack_angle = 180;
	_distance_acti = width;
	LoadResources();
	_physical.x = pos.x + width / 2 + _current_sprite->sprite_texture->frame_width;
}

CTank::~CTank()
{

}

void CTank::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	_live_sprite = new CSprite(rs->_enemy_tank);
	_die_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _live_sprite;
	_max_bullet = 3;
}

void CTank::Draw()
{
	CEnemy::Draw();
}

void CTank::Update(int delta_time)
{
	CResourcesManager *rs = CResourcesManager::GetInstance();

	_physical.SetBounds(0, 0, 0, 0);
	// set cho camera di chuyển
	if (rs->_camera->getState() == CamS_Follow && _count == 0
		&& rs->m_posBill.x > _physical.x - _distance_acti)
	{
		rs->_camera->setState(CamS_Move);
	}

	// Khi camera dưng lại mới update tank
	if (rs->_camera->getState() == CamS_Stop)
	{
		_physical.SetBounds(_physical.x, _physical.y, 80, 60);

		// khi tank ra khỏi view
		if (_physical.x + _live_sprite->sprite_texture->frame_width / 2 < rs->_camera->getPosX())
		{
			_can_impact = false;
			_physical.SetBounds(0, 0, 0, 0);
			rs->_camera->setState(CamS_Follow);
		}

		if (_enemy_status == EAttack)
		{
			//Target mục tiêu
			D3DXVECTOR2 pos_target = rs->m_posBill;
			SetTarget(pos_target.x, pos_target.y);

			//Cập nhật lại những viên đạn có thể bắn trong list của enemy
			_weapon->UpdateQueueIdBullet(_queue_id_bullet);
		}
		else if (_enemy_status == EWait)
		{
			_physical.vx = -0.04f;
			_distance_move += _physical.vx;
			_physical.CalcPositionWithoutGravitation(delta_time);
			if (_distance_move <= 0)
			{
				if (_count < 9)
				{
					_enemy_status = EAttack;
				}
				_physical.vx = 0;
			}

		}

		// hp = 0
		if (_hp == 0)
		{
			_enemy_status = EDie;
			_physical.vx = 0;
			_physical.SetBounds(0, 0, 0, 0);
			_can_impact = false;
			rs->_camera->setState(CamS_Follow);
		}
	}

}

void CTank::SetTarget(float x, float y)
{
	CEnemyUseGun::SetTarget(x, y - 20);
	Attacking();
}

void CTank::DrawWhenAttack(D3DXVECTOR3 pos)
{
	int num = 0;
	if (_hp <= 20 && _hp > 10)
	{
		num = 6;
	}
	else if (_hp <= 10 && _hp > 0)
	{
		num = 12;
	}
	else if (_hp > 20)
	{
		num = 0;
	}

	if (_attack_angle == 180)
	{
		_current_sprite->SelectFrameOf(num);
	}
	else if (_attack_angle == 240)
	{
		_current_sprite->SelectFrameOf(4 + num);

	}
	else if (_attack_angle == 210)
	{
		_current_sprite->SelectFrameOf(2 + num);
	}
	_current_sprite->Draw(pos.x, pos.y);
}

void CTank::DrawWhenWait(D3DXVECTOR3 pos)
{
	if (_hp <= 20 && _hp > 10)
	{
		_current_sprite->DrawWithDirection(pos, 1, 6, 7);
	}
	else if (_hp <= 10 && _hp > 0)
	{
		_current_sprite->DrawWithDirection(pos, 1, 12, 13);
	}
	else if (_hp >= 20)
	{
		_current_sprite->DrawWithDirection(pos, 1, 0, 1);
	}
}

void CTank::DrawWhenDie(D3DXVECTOR3 pos)
{
	if (_die_sprite->index != 2)
	{
		D3DXVECTOR3 posCal = pos;
		int x = 0;
		int y = 0;
		for (int i = 0; i < 6; i++)
		{
			x = (i % 3) * 20 - 15;
			y = (i / 3) * 20 - 10;
			posCal = D3DXVECTOR3(pos.x + x, pos.y + y, 0);
			_die_sprite->DrawWithDirectionAndOneTimeEffect(posCal, 1, 0, 2, 250);
		}
	}
}

void CTank::Attacking()
{

	if (_hp == 0) return;
	if (!CheckTarget()) return; //Mục tiêu chưa vào tầm tấn công

	DWORD now = GetTickCount();

	//Giãn cách bắn 
	if (now - _last_time_shoot >= ENEMY_SNIPER_STAND_ELAPSED_SHOOT)
	{

		if (_count >= 9 && _enemy_status == EAttack)
		{
			_enemy_status = EWait;
			_distance_move = 8;
		}

		//Kiểm tra số đạn đã bắn, nếu vẫn còn bắn được thì bắn
		if (_queue_id_bullet.size() < _max_bullet)
		{
			_count++;

			//2 góc liền kề với góc của mục tiêu
			int angle_1 = _target_angle / ENEMY_ATTACK_DEGREES * ENEMY_ATTACK_DEGREES;
			int angle_2 = angle_1 + ENEMY_ATTACK_DEGREES;

			_attack_angle = (angle_2 - _target_angle) < (_target_angle - angle_1) ? angle_2 : angle_1;
			_attack_angle %= 360;

			if (_attack_angle < 180) _attack_angle = 180;
			else if (_attack_angle > 240) _attack_angle = 240;

			//Chỉnh tọa độ bắn
			int x = _physical.x - 46;
			int y = _physical.y;

			if (_attack_angle == 180)
			{
				y += 19;
			}
			else if (_attack_angle == 240)
			{
				x += 5;
				y += 2;
			}
			else if (_attack_angle == 210)
			{
				y += 8;
				x += 3;
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