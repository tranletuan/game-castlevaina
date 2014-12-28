#include "CBoss3.h"

CBoss3::CBoss3(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 20;
	_is_hide = true;
	_last_time_hide = 0;
	_count_time_destroy = 0;
	_x_random = pos.x;
	_y_random = pos.y;
	_enable = false;
	LoadResources();
}

CBoss3::~CBoss3()
{
}

void CBoss3::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_live_sprite = new CSprite(rs->_boss3);
	_die_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _live_sprite;
}

void CBoss3::Draw()
{
	if (!_enable) return;
	CEnemy::Draw();
}

void CBoss3::Update(int delta_time)
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	CCamera* c = rs->_camera;
	if (c->view_port.y + c->getWidth() >= rs->m_widthMap) _enable = true;

	if (_hp == 0) SetStatus(EDie);
	if (!_enable || _hp <= 0) return;	
	//Target mục tiêu
	D3DXVECTOR3 pos_target = CResourcesManager::GetInstance()->m_posBill;
	SetTarget(pos_target.x, pos_target.y);

	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	if (!_is_hide)
	{
		if (_last_time_hide == 0) _last_time_hide = GetTickCount();
		DWORD now = GetTickCount();

		if (now - _last_time_hide >= BOSS3_ELAPSED_TIME_HIDE)
		{
			_enemy_status = EWait;
			_is_hide = true;
			_ready_shoot = false;
			_last_time_hide = 0;

			//Random tọa độ xuất hiện tiếp theo
			CCamera* c = CResourcesManager::GetInstance()->_camera;

			_x_random = (_target.x - BOSS3_RANDOM_DISTANCE_APPEAR_X) + rand() % (2 * BOSS3_RANDOM_DISTANCE_APPEAR_X);
			_y_random = c->getWidth() * 2 / 3 + rand() % BOSS3_RANDOM_DISTANCE_APPEAR_Y;

			D3DXVECTOR3 pos_check = c->Transform(_x_random, _y_random);
			if (pos_check.x - 60 < 0) _x_random = c->view_port.x + 60;
			if (pos_check.x + 60 > c->getWidth()) _x_random = c->view_port.x + c->getWidth() - 60;
		}
	}
	else
	{
		if (_last_time_appear == 0) _last_time_appear = GetTickCount();
		DWORD now = GetTickCount();
		
		if (now - _last_time_appear >= BOSS3_ELAPSED_TIME_APPEAR)
		{
			_enemy_status = EAttack;
			_is_hide = false;
			_last_time_appear = 0;

			_physical.x = _x_random;
			_physical.y = _y_random;
		}
	}

	switch (_enemy_status)
	{
	case EWait:
	case EDie:
		_can_impact = false;
		_physical.SetBounds(0, 0, 0, 0);
		break;
	case EAttack:
		_can_impact = true;
		_physical.SetBounds(_physical.x, _physical.y, 20, 20);
		break;
	}
}

void CBoss3::SetTarget(float x, float y)
{
	_target.x = x;
	_target.y = y;
	SetWeapon(CResourcesManager::GetInstance()->_weapon_enemy);
	Attacking();
}

void CBoss3::Attacking()
{ 
	if (_hp <= 0) return;
	if (_enemy_status != EAttack) return;
	if (!_ready_shoot) return;

	DWORD now = GetTickCount();

	if (_last_time_shoot_fb == 0) _last_time_shoot_fb = GetTickCount();
	if (now - _last_time_shoot_fb >= BOSS3_ELAPSED_TIME_SHOOT)
	{
		int id1 = _weapon->ShootingBulletFB(D3DXVECTOR3(_physical.x, _physical.y, 0), 270, 0);
		int id2 = _weapon->ShootingBulletB3(D3DXVECTOR3(_physical.x + 20, _physical.y + 15, 0), 0, 0);
		int id3 = _weapon->ShootingBulletB3(D3DXVECTOR3(_physical.x - 20, _physical.y + 15, 0), 180, 0);

		if (id1 >= 0)
		{
			_queue_id_bullet.push(id1);
		}

		if (id2 >= 0)
		{
			_queue_id_bullet.push(id1);
		}

		if (id3 >= 0)
		{
			_queue_id_bullet.push(id1);
		}

		_last_time_shoot_fb = 0;
	}

}

void CBoss3::DrawWhenAttack(D3DXVECTOR3 pos)
{
	if (!_ready_shoot)
	{
		_ready_shoot = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 10, 50);
	}
	else
	{
		_current_sprite->DrawWithDirection(pos, 1, 10, 11);
	}
}

void CBoss3::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite->Draw(pos.x, pos.y);
	if (_count_time_destroy < 3)
	{
		bool done = _die_sprite->PerformEffectOneTime(0, 2, 150);

		int x = pos.x - 12;
		int y = pos.y - 20;
		for (int i = 0; i < 2; i++)
		{
			_die_sprite->Draw(x, y);
			y += 30;
		}

		x = pos.x + 12;
		y = pos.y - 20;
		for (int i = 0; i < 2; i++)
		{
			_die_sprite->Draw(x, y);
			y += 30;
		}

		if (done)
		{
			_die_sprite->Reset();
			_count_time_destroy++;
		}
	}
	else
	{
		_enable = false;
	}
}

void CBoss3::DrawWhenWait(D3DXVECTOR3 pos)
{
	if (_current_sprite->index != 0)
	{
		_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 10, 0, 50);
	}
}
