#include "CRunmanFire.h"

CRunmanFire::CRunmanFire(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CRunman(id, specific_type, pos, width, height)
{
	_hp = 1;
	_max_bullet = ENEMY_RUN_MAN_FIRE_MAX_BULLET;
	LoadResources();
}

CRunmanFire::~CRunmanFire()
{
}

void CRunmanFire::Draw()
{
	CRunman::Draw();
}

void CRunmanFire::LoadResources()
{
	if (_specific_type == RunMan_Fire)
	{
		CResourcesManager* rs = CResourcesManager::GetInstance();
		CRunman::LoadResources();
		_attack_sprite = new CSprite(rs->_enemy_run_man_fire);
	}
}

void CRunmanFire::Update(int delta_time)
{

}

void CRunmanFire::SetTarget(D3DXVECTOR3 pos, D3DXVECTOR3 target)
{
}

void CRunmanFire::DrawWhenStand(D3DXVECTOR3 pos)
{
}

void CRunmanFire::DrawWhenRun(D3DXVECTOR3)
{
}

void CRunmanFire::DrawWhenAttack(D3DXVECTOR3 pos)
{
}

void CRunmanFire::DrawWhenJump(D3DXVECTOR3 pos)
{
}

void CRunmanFire::DrawWhenDie(D3DXVECTOR3 pos)
{
}
