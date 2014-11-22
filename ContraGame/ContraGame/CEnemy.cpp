#include "CEnemy.h"

CEnemy::CEnemy(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Enemy, pos, width, height)
{
	_enemy_status = EWait;
	_physical.vx_last = -1;
}

CEnemy::~CEnemy()
{
}

void CEnemy::LoadResources()
{

}

void CEnemy::Update(float delta_time)
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
	if (abs(_physical.x - _target.x) <= ENEMY_ATTACK_DISTANCE)
	{
		return true;
	}

	return false;
}