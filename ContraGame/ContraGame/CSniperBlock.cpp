#include "CSniperBlock.h"

CSniperBlock::CSniperBlock(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Enemy, pos, width, height)
{
	_timeDuring = 40;
	_state = SBS_Wait;
	_hp = 3;
	LoadResources();
}

CSniperBlock::~CSniperBlock()
{

}

void CSniperBlock::LoadResources()
{
	_current_sprite = new CSprite(CResourcesManager::GetInstance()->_enemy_sniper_block);
	_sprite_effect = new CSprite(CResourcesManager::GetInstance()->_effect_destroy);
}

void CSniperBlock::Draw()
{
	CCamera *cam = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = cam->Transform(_physical.x, _physical.y);

	switch (_state)
	{
	case SBS_Wait:
		DrawWhenWait(pos);
		break;
	case SBS_Fire:
		DrawWhenFire(pos);
		break;
	case SBS_Die:
		DrawWhenDie(pos);
		break;
	default:
		break;
	}
}

void CSniperBlock::Update(int delta_time)
{
	switch (_state)
	{
	case SBS_Wait:
		_timeDuring--;
		if (_timeDuring <= 0)
		{
			_state = SBS_Fire;
			_timeDuring = 40;
		}
		break;
	case SBS_Fire:

		break;
	case SBS_Die:

		break;
	default:
		break;
	}

	if (_hp == 0)
	{
		_state = SBS_Die;
	}
}

void CSniperBlock::DrawWhenWait(D3DXVECTOR3 pos)
{
	_current_sprite->SelectFrameOf(0);
	_current_sprite->Draw(pos.x, pos.y);
}

void CSniperBlock::DrawWhenDie(D3DXVECTOR3 pos)
{
	if (_sprite_effect->index != 2)
	{
		_sprite_effect->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 2,200);
	}
}

void CSniperBlock::DrawWhenFire(D3DXVECTOR3 pos)
{
	if (_current_sprite->index != 1)
	{
		_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 1,200);
	}
	else
	{
		_state = SBS_Wait;		
		_current_sprite->Reset();
	}
}