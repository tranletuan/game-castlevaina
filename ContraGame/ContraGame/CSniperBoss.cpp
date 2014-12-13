#include "CSniperBoss.h"

CSniperBoss::CSniperBoss(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 1;
	LoadResources();
}

CSniperBoss::~CSniperBoss()
{
}

void CSniperBoss::LoadResources()
{
}

void CSniperBoss::Draw()
{
}

void CSniperBoss::Update(int delta_time)
{
}

void CSniperBoss::SetTarget(float x, float y)
{
}

void CSniperBoss::Attacking()
{
}

void CSniperBoss::DrawWhenAttack(D3DXVECTOR3 pos)
{
}

void CSniperBoss::DrawWhenDie(D3DXVECTOR3 pos)
{
}

void CSniperBoss::DrawWhenWait(D3DXVECTOR3 pos)
{
}
