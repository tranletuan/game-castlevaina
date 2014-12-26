#include "CEnemy.h"

CEnemy::CEnemy(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Enemy, pos, width, height)
{
	_enemy_status = EWait;
	_enable = true;
	_physical.vx_last = -1;
}

CEnemy::~CEnemy()
{
	delete _live_sprite;
	delete _die_sprite;
}

void CEnemy::LoadResources()
{

}

void CEnemy::Update(int delta_time)
{

}

void CEnemy::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	switch (_enemy_status)
	{
	case EWait:
		DrawWhenWait(pos);
		break;
	case EAttack:
		DrawWhenAttack(pos);
		break;
	case EDie:
		DrawWhenDie(pos);
		break;
	}
}

void CEnemy::SetTarget(float x, float y)
{
	_target.x = x;
	_target.y = y;
}

bool CEnemy::SetStatus(EnemyStatus status)
{
	if (status >= _enemy_status)
	{
		_enemy_status = status;
		return true;
	}

	return false;
}

bool CEnemy::CheckTarget()
{
	bool flag = false;
	switch (CResourcesManager::GetInstance()->m_curMap)
	{
	case 2:
		flag = (abs(_physical.y - _target.y) <= ENEMY_ATTACK_DISTANCE);
		break;
	case 1:
	case 3:
		flag = (abs(_physical.x - _target.x) <= ENEMY_ATTACK_DISTANCE);
		break;
	}

	return flag;
}