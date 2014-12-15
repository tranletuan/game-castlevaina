#include "CRockRoll.h"

CRockRoll::CRockRoll(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	: CObject(id, specific_type, Enemy, pos, width, height)
{
	_state = RS_Wait;
	_hp = 3;
	_idGround = -1;
	_posYBegin = pos.y;
	_timeDruing = 60;

	LoadResources();
}

CRockRoll::~CRockRoll()
{

}

void CRockRoll::LoadResources()
{
	_current_sprite = new CSprite(CResourcesManager::GetInstance()->_enemy_rock_roll);
	_sprite_effect = new CSprite(CResourcesManager::GetInstance()->_effect_destroy);
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
	case RS_Up:
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
	_current_sprite->DrawWithDirection(pos, 1, 0, 2);
}

void CRockRoll::DrawWhenMove(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirection(pos, 1, 3, 4);
}

void CRockRoll::DrawWhenDie(D3DXVECTOR3 pos)
{
	if (_sprite_effect->index == 2 )
	{		
		_state = RS_OutView;
	}
	else
	{
		_sprite_effect->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 2);
	}

}

void CRockRoll::Update(int delta_time)
{
	float _posYBill = CResourcesManager::GetInstance()->m_posBill.y;
	float _posYCam = CResourcesManager::GetInstance()->_camera->getPosY()
		- CResourcesManager::GetInstance()->_camera->getHeight();  // điểm dưới của camera
	vector<CObject*> Obs = CResourcesManager::GetInstance()->listObinView;
	
	// vang ra khoi screen
	if (_posYCam >= _physical.y )
	{
		_state = RS_OutView;
	}

	switch (_state)
	{
	case RS_Wait:
		if (_physical.y - _posYBill <= 20)
		{			
			_state = RS_Fall;
		}
		break;
	case RS_Fall:
		_physical.CalcPositionWithGravitation(delta_time, 0.005);
		_physical.SetBounds(_physical.x,_physical.y,28,28);		

		// xet va cham voi ground
		for (int i = 0; i < Obs.size(); i++)
		{
			if (Obs.at(i)->getSpecificType() == Ground_Grass)
			{
				CollisionDirection collision = NoCollision;
				if (Obs.at(i)->getID() != _idGround)
				{					
					collision = _physical.Collision(&Obs.at(i)->_physical);
					if (collision == TopCollision)
					{
						_state = RS_Up;
						_idGround = Obs.at(i)->getID();
						_physical.vy = 1;
						break;
					}
				}
			}
		}


		break;
	case RS_Up:
		_physical.CalcPositionWithGravitation(delta_time, 0.001);
		if (_physical.current_vy <= 0)
		{
			_physical.time_in_space = 0;
			_physical.vy = 0;
			_state = RS_Fall;
		}
		break;
	case RS_Die:
	
		break;
	case RS_OutView:
		_timeDruing--;
		if (_timeDruing <= 0)
		{
			_physical.y = _posYBegin;
			_physical.vy = 0;
			_physical.n = 0;
			_physical.time_in_space = 0;		
			_state = RS_Wait;
			_sprite_effect->Reset();
			_timeDruing = 60;
			_hp = 3;
		}
		break;
	default:
		break;
	}

	// het mau hp
	if (_hp == 0 && _state != RS_Die)
	{
		_state = RS_Die;
	}

}