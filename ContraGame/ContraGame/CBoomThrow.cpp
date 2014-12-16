#include "CBoomThrow.h"

CBoomThrow::CBoomThrow(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Enemy, pos, width, height)
{
	_timeDuring = 20;
	_state = BoS_Throw;
	_posBegin = pos;
	_physical.vx = 
	LoadResources();
}

void CBoomThrow::LoadResources()
{
	_current_sprite = new CSprite(CResourcesManager::GetInstance()->_enemy_boom_throw);
	_sprite_effect = new CSprite(CResourcesManager::GetInstance()->_effect_die);
}

void CBoomThrow::Draw()
{
	CCamera* cam = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3  pos = cam->Transform(_physical.x, _physical.y);

	switch (_state)
	{
	case BoS_Wait:
		break;
	case BoS_Die:
		DrawWhenDie(pos);
		break;
	case BoS_Throw:
		DrawWhenThrow(pos);
		break;
	default:
		break;
	}
}

void CBoomThrow::Update(int delta_time)
{
	switch (_state)
	{
	case BoS_Wait:
		_timeDuring--;
		if (_timeDuring <= 0)
		{

		}
		break;
	case BoS_Die:
		break;
	case BoS_Throw:
		
		break;
	default:
		break;
	}
}

void CBoomThrow::DrawWhenDie(D3DXVECTOR3 pos)
{

}

void CBoomThrow::DrawWhenThrow(D3DXVECTOR3 pos)
{

}

CBoomThrow::~CBoomThrow()
{

}