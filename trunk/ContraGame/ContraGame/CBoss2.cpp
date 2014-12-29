#include "CBoss2.h"

CBoss2::CBoss2(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 30;
	_is_shot = false;
	_enable = false;
	_last_time_shoot = 0;
	_count_time_undying = 0;
	LoadResources();
}

CBoss2::~CBoss2()
{
}

void CBoss2::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_live_sprite = new CSprite(rs->_boss2_live);
	_die_sprite = new CSprite(rs->_boss2_die);
	_destroy_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _live_sprite;
}

void CBoss2::Update(int time)
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	CCamera* c = rs->_camera;
	if (c->view_port.y == rs->m_heightMap) _enable = true;

	if (!_enable) return;

	if (_hp <= 0)
	{
		_physical.SetBounds(0, 0, 0, 0);
		SetStatus(EDie);
		return;
	}

	//Target mục tiêu
	D3DXVECTOR3 pos_target = CResourcesManager::GetInstance()->m_posBill;
	SetTarget(pos_target.x, pos_target.y);

	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	//Khi đã bắn ra 1 viên đạn và viên đạn hết hiệu lực thì trở về trạng thái chờ
	if (_is_shot && _queue_id_bullet.size() == 0)
	{
		_is_shot = false;
		_enemy_status = EWait;
	}

	//Chờ bắn đợt đạn tiếp theo
	if (_enemy_status == EWait)
	{
		if (_last_time_shoot == 0)	_last_time_shoot = GetTickCount();

		DWORD now = GetTickCount();
		if (now - _last_time_shoot >= BOSS2_ELAPSED_TIME_SHOOT)
		{
			//Khoảng thời gian đầu boss bất tử
			if (_count_time_undying >= BOSS2_MAX_TIME_UNDYING)
			{
				SetStatus(EAttack);
			}
			else
			{
				_count_time_undying++;
			}

			_last_time_shoot = 0;
		}
	}

	//Thiết lập khung bao cho boss
	if (_count_time_undying < BOSS2_MAX_TIME_UNDYING)
		_physical.SetBounds(0, 0, 0, 0);
	else
	{
		_physical.SetBounds(_physical.x, _physical.y + 64, 20, 20);
		_can_impact = true;
	}
}

void CBoss2::Draw()
{
	if (!_enable) return;
	CEnemy::Draw();
}

void CBoss2::DrawWhenWait(D3DXVECTOR3 pos)
{
	if (_current_sprite->index < 3)
	{
		_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 2, BOSS2_ARM_ELAPSED_CHANGE / 3);
	}
	else if (_current_sprite->index > 5)
	{
		_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 8, 5, 200);
	}
	else
	{
		_current_sprite->DrawWithDirection(pos, 1, 3, 5, 200);
	}
}

void CBoss2::DrawWhenAttack(D3DXVECTOR3 pos)
{
	if (!_ready_shoot)
	{
		_ready_shoot = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 6, 8, 200);
	}
	else
	{
		_current_sprite->DrawWithDirection(pos, 1, 9, 11, 200);
	}
}

void CBoss2::DrawWhenDie(D3DXVECTOR3 pos)
{
	if (_count_time_destroy < 3)
	{
		_current_sprite->SelectFrameOf(3);
		_current_sprite->Draw(pos.x, pos.y);

		bool done = _destroy_sprite->PerformEffectOneTime(0, 2, 150);

		//effect trái
		int x = pos.x - 16;
		int y = pos.y + 44;
		for (int i = 0; i < 4; i++)
		{
			_destroy_sprite->Draw(x, y);
			y -= 32;
		}
		_destroy_sprite->Draw(x - 32, y + 32);

		//effect phải
		x = pos.x + 16;
		y = pos.y + 44;
		for (int i = 0; i < 4; i++)
		{
			_destroy_sprite->Draw(x, y);
			y -= 32;
		}
		_destroy_sprite->Draw(x + 32, y + 32);

		if (done)
		{
			_count_time_destroy++;
			_destroy_sprite->Reset();
		}
	}
	else
	{
		_current_sprite = _die_sprite;
		_current_sprite->Draw(pos.x, pos.y);
	}
}

void CBoss2::SetTarget(float x, float y)
{
	_target.x = x;
	_target.y = y;

	if (_ready_shoot)
	{
		SetWeapon(CResourcesManager::GetInstance()->_weapon_enemy);
		Attacking();
	}
}

void CBoss2::Attacking()
{
	if (_hp == 0) return;
	if (_enemy_status != EAttack) return;
	if (_weapon == NULL) return;

	//Kiểm tra số đạn đã bắn
	if (_queue_id_bullet.size() == 0)
	{
		//Chỉnh tọa độ bắn
		int x = _physical.x;
		int y = _physical.y + 54;

		int id1 = _weapon->ShootingBulletB2(D3DXVECTOR3(x, y, 0), 240, 0);
		int id2 = _weapon->ShootingBulletB2(D3DXVECTOR3(x, y, 0), 270, 0);
		int id3 = _weapon->ShootingBulletB2(D3DXVECTOR3(x, y, 0), 300, 0);

		if (id1 >= 0)
		{
			_queue_id_bullet.push(id1);
			_is_shot = true;
		}

		if (id2 >= 0)
		{
			_queue_id_bullet.push(id2);
			_is_shot = true;
		}

		if (id3 >= 0)
		{
			_queue_id_bullet.push(id3);
			_is_shot = true;
		}
	}
}