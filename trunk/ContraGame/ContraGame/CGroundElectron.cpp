#include "CGroundElectron.h"

CGroundElectron::CGroundElectron(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEffectObject(id, specific_type, pos, width, height)
{
	LoadResources();
}

CGroundElectron::~CGroundElectron()
{

}

void CGroundElectron::LoadResources()
{
	_current_sprite = new CSprite(CResourcesManager::GetInstance()->_ground_electron);
}

void CGroundElectron::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	_current_sprite->DrawWithDirection(pos,1,0,1,200);
}

void CGroundElectron::Update(int delta_time)
{

}