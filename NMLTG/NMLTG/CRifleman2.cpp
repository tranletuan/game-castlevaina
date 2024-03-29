#include "CRifleman2.h"

CRifleman2::CRifleman2(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
}

CRifleman2::~CRifleman2()
{
}

void CRifleman2::Moving(float v)
{
}

void CRifleman2::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_live_sprite = new CSprite(rs->_enemy_rifleman_2);
	_die_sprite = new CSprite(rs->_effect_die);
}

void CRifleman2::Draw()
{
	CEnemy::Draw();
}

void CRifleman2::Update(int delta_time)
{
	//Khi hp = 0 cho lính nhảy lên
	if (_hp == 0 && _physical.current_vy >= 0)
	{
		_physical.vx = 0;
		_physical.vy = ENEMY_VY_DIE;
		_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
	}

	//Khi đạt độ cao cực đại thì trạng thái chuyển sang die
	if (_physical.current_vy < 0)
	{
		SetStatus(EDie);
	}
}

void CRifleman2::Attacking(CEnemyWeapon* weapon)
{

}

void CRifleman2::DrawWhenAttack(D3DXVECTOR3 pos)
{
}

void CRifleman2::DrawWhenWait(D3DXVECTOR3 pos)
{
}

void CRifleman2::DrawWhenDie(D3DXVECTOR3 pos)
{
}