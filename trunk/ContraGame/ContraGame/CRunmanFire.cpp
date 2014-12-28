#include "CRunmanFire.h"

CRunmanFire::CRunmanFire(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CRunman(id, specific_type, pos, width, height)
{
	_hp = 1;
	LoadResources();
}

CRunmanFire::~CRunmanFire()
{
}

void CRunmanFire::LoadResources()
{
	if (_specific_type == RunMan_Fire)
	{
		CRunman::LoadResources();
		CResourcesManager* rs = CResourcesManager::GetInstance();
		_attack_sprite = new CSprite(rs->_enemy_run_man_fire);
	}
}

void CRunmanFire::Update(int delta_time)
{
	if (!_enable) return;
	CRunman::Update(delta_time);

	//Target mục tiêu
	D3DXVECTOR3 pos_target = CResourcesManager::GetInstance()->m_posBill;
	SetTargetAttack(pos_target.x, pos_target.y);

	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	if (_rm_status == RMAttack)
	{	
		DWORD now = GetTickCount();
		if (_last_time_shoot == 0) _last_time_shoot = GetTickCount();
		
		if (now - _last_time_shoot >= ENEMY_RUN_MAN_FIRE_TIME_WAIT)
		{
			_rm_status = RMRun;
			_physical.vx = _physical.vx_last > 0 ? ENEMY_RUN_MAN_VX : -ENEMY_RUN_MAN_VX;
			_current_sprite = _live_sprite;
			_last_time_shoot = 0;
		}
	}
}

void CRunmanFire::DrawWhenAttack(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 1, 300);
}

void CRunmanFire::SetTarget(D3DXVECTOR3 pos, D3DXVECTOR3 target)
{
	CRunman::SetTarget(pos, target);
	_count_bullet = 0;
}

void CRunmanFire::SetTargetAttack(float x, float y)
{
	float distance_x = _physical.x > x ? _physical.x - x : x - _physical.x;
	float distance_y = _physical.y > y ? _physical.y - y : y - _physical.y;

	if (distance_y <= ENEMY_RUN_MAN_FIRE_ATTACK_DISTANCE &&
		distance_x <= ENEMY_RUN_MAN_FIRE_ATTACK_DISTANCE + 30 &&
		_count_bullet < ENEMY_RUN_MAN_FIRE_MAX_BULLET &&
		_rm_status == RMRun)
	{
		SetWeapon(CResourcesManager::GetInstance()->_weapon_enemy);
		Attacking();
	}
}

void CRunmanFire::Attacking()
{
	if (_hp == 0) return;
	if (_weapon == NULL) return;

	//Kiểm tra số đạn đã bắn
	if (_queue_id_bullet.size() == 0)
	{
		//Chỉnh tọa độ bắn
		int x = _physical.vx_last > 0 ? _physical.x + 12 : _physical.x - 12;
		int y = _physical.y + 10;
		int attack_angle = _physical.vx_last > 0 ? 0 : 180;

		int id = _weapon->ShootingBulletNE(D3DXVECTOR3(x, y, 0), attack_angle, 0);

		if (id >= 0)
		{
			_queue_id_bullet.push(id);
			_current_sprite = _attack_sprite;
			_current_sprite->Reset();
			_physical.vx = 0;
			_count_bullet++;
			SetStatus(RMAttack);
		}
	}
	
}