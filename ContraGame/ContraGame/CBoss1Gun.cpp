#include "CBoss1Gun.h"

CBoss1Gun::CBoss1Gun(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 20;
	_can_impact = true;
	LoadResources();
}

CBoss1Gun::~CBoss1Gun()
{
}

void CBoss1Gun::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	if (_specific_type == Boss1_Gun)
	{
		_live_sprite = new CSprite(rs->_boss1_gun);
		_die_sprite = new CSprite(rs->_effect_destroy);
		_current_sprite = _live_sprite;
		_max_bullet = BOSS1_GUN_MAX_BULLET;
	}

}

void CBoss1Gun::Draw()
{
	CEnemy::Draw();
}

void CBoss1Gun::Update(int delta_time)
{
	//Target mục tiêu
	D3DXVECTOR2 pos_target = CResourcesManager::GetInstance()->m_posBill;
	SetTarget(pos_target.x, pos_target.y);

	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	if (_hp == 0)
	{
		SetStatus(EDie);
	}

	switch (_enemy_status)
	{
	case EWait:
	case EAttack:
		_physical.SetBounds(
			_physical.x,
			_physical.y,
			_current_sprite->sprite_texture->width / 2,
			_current_sprite->sprite_texture->height);
		break;
	case EDie:
		_physical.SetBounds(0, 0, 0, 0);
		break;
	}
}

void CBoss1Gun::SetTarget(float x, float y)
{
	_target.x = x;
	_target.y = y;

	if (_physical.x - _target.x > 200) return;
	
	CEnemyWeapon* wp = CResourcesManager::GetInstance()->_weapon_enemy;
	SetWeapon(wp);
	Attacking();
}

void CBoss1Gun::Attacking()
{
	if (_hp == 0) return;
	if (_enemy_status != EWait) return;

	DWORD now = GetTickCount();
	//Kiểm tra số đạn đã bắn, nếu vẫn còn bắn được thì bắn
	if (now - _last_time_shoot >= BOSS1_GUN_ELAPSED_SHOOT)
	{
		if (_queue_id_bullet.size() < _max_bullet)
		{
			float x = _physical.x - 10;
			float y = _physical.y;

			//Bắn
			int id = _weapon->ShootingBulletB(D3DXVECTOR3(x, y, 0));

			if (id >= 0)
			{
				_queue_id_bullet.push(id);
				SetStatus(EAttack);
			}
		}

		_last_time_shoot = now;
	}
}

void CBoss1Gun::DrawWhenAttack(D3DXVECTOR3 pos)
{
	bool done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, -1, 0, 1, 150);

	if (done)
	{
		_enemy_status = EWait;
	}
}

void CBoss1Gun::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirection(pos, -1, 2, 2);

	if (_die_sprite->index != 2)
	{
		_die_sprite->DrawWithDirectionAndOneTimeEffect(pos, -1, 0, 2, 200);
	}
}

void CBoss1Gun::DrawWhenWait(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirection(pos, -1, 0, 0);
}

