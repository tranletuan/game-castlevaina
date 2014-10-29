#include "CBill.h"

CBill::CBill(D3DXVECTOR3 pos, int size)
{
	_physical = CPhysical(pos.x, pos.y, size, size);
	_physical.vx_last = BILL_VX;
	_enviroment = Land;
	_gun_direction = Normal;
	_player_status = Stand;
	_physical.time_in_space = 0;
	_physical.vx = 0;
}

CBill::~CBill()
{
	delete _bill_stand;
	delete _bill_jump;
	delete _bill_die;
	delete _bill_move;
	delete _bill_in_water;
}

void CBill::LoadResources()
{
	CResourcesManager* rm = CResourcesManager::GetInstance();

	_bill_stand = new CSprite(rm->_bill_stand);
	_bill_jump = new CSprite(rm->_bill_jump);
	_bill_die = new CSprite(rm->_bill_die);
	_bill_move = new CSprite(rm->_bill_move);
	_bill_in_water = new CSprite(rm->_bill_in_water);

	_current_sprite = _bill_stand;

}

void CBill::Draw()
{
	CCamera* camera = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = camera->Transform(_physical.x, _physical.y);
	
	switch (_player_status)
	{
	case Move:
		DrawWhenMove(pos);
		break;
	case Stand:
		DrawWhenStand(pos);
		break;
	case Jump:
		DrawWhenJump(pos);
		break;
	case Die:
		DrawWhenDie(pos);
		break;
	}


}

void CBill::Update(int delta_time)
{
	_physical.CalcPositionWithGravitation(delta_time);
}

void CBill::SetStatus(PlayerStatus stt)
{
	if (_player_status != Die || _player_status != Jump || (_player_status == Jump && stt == Die))
	{
		_player_status = stt;
	}
}

void CBill::SetEnviroment(Environment env)
{
	_enviroment = env;
}

void CBill::SetGunDirection(GunDirection gd)
{
	_gun_direction = gd;
}

void CBill::Moving(float vx)
{
	_physical.vx = vx;
	_physical.vx_last = vx;
	SetStatus(Move);
}

void CBill::Standing()
{
	_physical.vx = 0;
	_physical.vy = 0;
	_physical.time_in_space = 0;
	SetStatus(Stand);
}

void CBill::Jumping()
{
	if (_enviroment != Water)
	{
		_physical.vy = BILL_VY;
		_physical.time_in_space = GetTickCount();
		SetStatus(Jump);
	}
}

void CBill::Attacking()
{
	
}

void CBill::Dying()
{
	SetStatus(Die);
}

void CBill::DrawWhenMove(D3DXVECTOR3 pos)
{
	if (_enviroment == Water)
	{
		_current_sprite = _bill_in_water;
		_current_sprite->DrawWithDirecion(pos, _physical.vx_last);
	}
	else
	{
		_current_sprite = _bill_move;
		switch (_gun_direction)
		{
		case Normal:
			_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 0, 4);
			break;
		case Up:
			_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 10, 14);
			break;
		case Down:
			_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 15, 19);
			break;
		}
	}
}

void CBill::DrawWhenStand(D3DXVECTOR3 pos)
{
	if (_enviroment == Water)
	{
		_current_sprite = _bill_in_water;
		_current_sprite->DrawWithDirecion(pos, _physical.vx_last);
	}
	else if (_enviroment == Land)
	{
		_current_sprite = _bill_stand;
		switch (_gun_direction)
		{
		case Normal:
			_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 0, 0);
			break;
		case Up:
			_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 2, 2);
			break;
		case Down:
			_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 4, 4);
			break;
		}
	}
}

void CBill::DrawWhenJump(D3DXVECTOR3 pos)
{
	_current_sprite = _bill_jump;
	_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 0, 3);
}

void CBill::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _bill_die;
	_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 0, 4);
}

void CBill::DrawWhenAttack(D3DXVECTOR3 pos)
{
	if (_enviroment == Water)
	{
		_current_sprite = _bill_in_water;

	}
	else if (_enviroment == Land)
	{
		
	}
}