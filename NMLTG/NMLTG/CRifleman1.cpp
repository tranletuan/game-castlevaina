#include "CRifleman1.h"

CRifleman1::CRifleman1(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 1;
}

CRifleman1::~CRifleman1()
{

}

void CRifleman1::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	if (_specific_type == Rifleman1)
	{
		_live_sprite = new CSprite(rs->_enemy_rifleman_1);
	}
	
	_die_sprite = new CSprite(rs->_effect_die);
	_current_sprite = _live_sprite;
}

void CRifleman1::Draw()
{
	CEnemy::Draw();
}

void CRifleman1::Attacking(CEnemyWaepon* waepon)
{

}

void CRifleman1::DrawWhenAttack()
{}


void CRifleman1::DrawWhenHide()
{}


void CRifleman1::DrawWhenDie()
{}