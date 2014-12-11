#include "CRockRoll.h"

CRockRoll::CRockRoll(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
 : CObject(id, specific_type, Enemy, pos, width, height)
{ 
	_state = RS_Wait;
	_hp = 1;
	_firstY = -1;
	LoadResources();
}

CRockRoll::~CRockRoll()
{

}

void CRockRoll::LoadResources()
{	
	_current_sprite = new CSprite(CResourcesManager::GetInstance()->_enemy_rock_roll);
}

void CRockRoll::Draw()
{
	D3DXVECTOR3 pos = CResourcesManager::GetInstance()->_camera->Transform(_physical.x, _physical.y);
	switch (_state)
	{
	case RS_Wait:
		DrawWhenWait(pos);
		break;
	case RS_Fall:	
	case RS_Through:
		DrawWhenMove(pos);
		break;
	case RS_Die:
		DrawWhenDie(pos);
		break;
	default:
		break;
	}
}

void CRockRoll::DrawWhenWait(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirection(pos, 1, 0, 1);
}

void CRockRoll::DrawWhenMove(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirection(pos, 1, 2, 3);
}

void CRockRoll::DrawWhenDie(D3DXVECTOR3 pos)
{
}

void CRockRoll::Update(int delta_time)
{

}