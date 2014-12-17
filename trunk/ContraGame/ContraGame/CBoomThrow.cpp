#include "CBoomThrow.h"

CBoomThrow::CBoomThrow(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Enemy, pos, width, height)
{
	_timeDuring = 20;
	_state = BoS_Throw;
	_posBegin = pos;
	_physical.vx = ENEMY_BOOM_THROW_VX;
	_physical.vy = ENEMY_BOOM_THROW_VY;
	_hp = 1;
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
	vector<CObject*> Obs = CResourcesManager::GetInstance()->listObinView;

	switch (_state)
	{
	case BoS_Wait:
		_timeDuring--;
		if (_timeDuring <= 0)
		{
			_sprite_effect->Reset();
			_current_sprite->Reset();
			_physical.x = _posBegin.x;
			_physical.y = _posBegin.y;
			_physical.vx = ENEMY_BOOM_THROW_VX;
			_physical.vy = ENEMY_BOOM_THROW_VY;
			_hp = 1;
			_state = BoS_Throw;
			_timeDuring = 20;
		}
		break;
	case BoS_Die:
		break;
	case BoS_Throw:
		_physical.CalcPositionWithGravitation(delta_time, ENEMY_BOOM_THROW_GRAVITY);
		_physical.SetBounds(_physical.x, _physical.y, 16, 16);

		// xet va cham voi ground
		for (int i = 0; i < Obs.size(); i++)
		{
			if (Obs.at(i)->getSpecificType() == Ground_Grass)
			{
				CollisionDirection collision = NoCollision;
				collision = _physical.Collision(&Obs.at(i)->_physical);
				if (collision == TopCollision)
				{
					_state = BoS_Die;
					_physical.vx = 0;
					_physical.vy = 0;
					_physical.time_in_space = 0;
					break;
				}
			}
		}
		break;
	default:
		break;
	}

	// Trướng hợp ném trúng con bill, thì hp-- + chuyển trạng thái nổ tại đây
	if (_hp == 0 && _state == BoS_Throw)
	{
		_state = BoS_Die;
		_physical.vx = 0;
		_physical.vy = 0;
		_physical.time_in_space = 0;
	}
}

void CBoomThrow::DrawWhenDie(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 posDie = D3DXVECTOR3(pos.x, pos.y + 10, 0);
	if (_sprite_effect->index != 2)
	{
		_sprite_effect->DrawWithDirectionAndOneTimeEffect(posDie, 1, 0, 2);
	}
	else
	{
		_state = BoS_Wait;
	}

}

void CBoomThrow::DrawWhenThrow(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirection(pos, 1, 0, 3);
}

CBoomThrow::~CBoomThrow()
{

}