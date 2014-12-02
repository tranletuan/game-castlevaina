#include "CBossGun.h"

CBossGun::CBossGun(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 15;
	LoadResources();
}

CBossGun::~CBossGun()
{
}

void CBossGun::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	if (_specific_type == Boss_Gun)
	{
		//_live_sprite = new CSprite(
	}
}

void CBossGun::Draw()
{
}

void CBossGun::Update(int delta_time)
{
}

void CBossGun::SetTarget(float x, float y)
{
}

void CBossGun::DrawWhenAttack(D3DXVECTOR3 pos)
{
}

void CBossGun::DrawWhenDie(D3DXVECTOR3 pos)
{

}

void CBossGun::DrawWhenWait(D3DXVECTOR3 pos)
{

}

void CBossGun::Attacking()
{

}