#include "CEnemy.h"

CEnemy::CEnemy(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Enemy, pos, width, height)
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	switch (_enemy_status)
	{
	case Hide:
		DrawWhenHide();
		break;
	case Attack:
		DrawWhenAttack();
		break;
	case Die:
		DrawWhenDie();
		break;
	}
}

void CEnemy::SetTarget(float x, float y)
{
	_target.x = x;
	_target.y = y;
}