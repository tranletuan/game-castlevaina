#include "CBill.h"

CBill::CBill(int id, SpecificType specific_type, D3DXVECTOR3 pos)
	:CObject(id, specific_type, Player, pos)
{
	_physical.vx_last = 1;
	_enviroment = Land;
	_gun_direction = Normal;
	_player_status = Stand;
	_physical.time_in_space = 0;
	_physical.vx = 0;
	_physical.SetBounds(pos.x, pos.y, 20, 32);
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
	_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
	_physical.SetBounds(
		_physical.x,
		_physical.y,
		20,
		32
		);
}

void CBill::SetStatus(PlayerStatus status)
{
	if (status >= _player_status)
	{
		_player_status = status;
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

//ACTIONS
void CBill::Dying()
{
	SetStatus(Die);

	int sign = _physical.vx_last > 0 ? -1 : 1;
	_physical.vx = BILL_VX * sign;
	_physical.vy = BILL_VY_DIE;
}

void CBill::Jumping()
{
	SetStatus(Jump);

	//Khi trạng thái != Die thì mới nhảy
	if (_player_status != Die)
	{	
		_physical.vy = BILL_VY;
	}
}

void CBill::Attacking(CPlayerWaepon* waepon)
{
	SetStatus(Attack);

	D3DXVECTOR3 pos;
	int angle = 0;
	float x = _physical.vx_last > 0 ? _physical.bounds.right : _physical.bounds.left;
	float y = 0;

	switch (_gun_direction)
	{
	case Normal:
		y = _physical.y;
		angle = _physical.vx_last > 0 ? angle : angle + 180;
		break;
	case Up:
		if (_physical.vx != 0)
		{
			y = _physical.y + 10;
			angle = 45;
			angle = _physical.vx_last > 0 ? angle : 180 - angle;
		}
		else
		{
			y = _physical.y + _current_sprite->sprite_texture->frame_height / 2;
			angle = 90;
		}
		break;
	case Down:
		if (_physical.vx != 0)
		{
			y = _physical.y - 10;
			angle = -45;
			angle = _physical.vx_last > 0 ? angle : -180 - angle;
		}
		else
		{
			y = _physical.y - _current_sprite->sprite_texture->frame_height / 2;
			angle = -90;
		}
		break;
	}

	pos = D3DXVECTOR3(x, y, 0);
	waepon->Shooting(pos, angle, _physical.vx);
}

void CBill::Moving(float vx)
{
	SetStatus(Move); //set trạng thái theo độ ưu tiên

	//Khi trạng thái hiện tại != die mới thay đổi vx
	if (_player_status != Die)
	{
		_physical.vx = vx;
		if (vx == 0)
		{
			if (_player_status != Jump)
			{
				_player_status = Stand;
			}
		}
		else
		{
			_physical.vx_last = vx;
		}
	}
}

void CBill::Standing(float y_ground)
{
	//Khi đang rơi mà va chạm mặt đất
	if (_physical.n == 0)
	{
		if (_player_status != Die)
		{
			_player_status = Stand;
		}
		else
		{
			_physical.vx = 0;
		}

		_physical.vy = 0;
	}

	_physical.n = GRAVITY;
	_physical.time_in_space = GetTickCount();
	_physical.y = y_ground;
}

//SUPPORT
void CBill::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _bill_die;
	
	_current_sprite->PerformEffectOneTime(0, 4, 100);
	
	if (_physical.vx_last > 0)
	{
		_current_sprite->Draw(pos.x, pos.y);
	}
	else
	{
		_current_sprite->DrawFlipX(pos.x, pos.y);
	}
	
}

void CBill::DrawWhenJump(D3DXVECTOR3 pos)
{
	_current_sprite = _bill_jump;
	_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 0, 3);
}

void CBill::DrawWhenAttack(D3DXVECTOR3 pos)
{
	//Bắn dưới nước
	if (_enviroment == Water)
	{
		_current_sprite = _bill_in_water;
		switch (_gun_direction)
		{
		case Normal:
			_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 2, 2);
			break;
		case Up:
			//Khi nhắm lên bắn có 2 kiểu, khi di chuyển hướng sung xéo
			//còn khi đứng yên hướng súng 90 độ
			if (_physical.vx != 0)
			{
				_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 3, 3);
			}
			else
			{
				_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 4, 4);
			}
			break;
		}
	}
	//Bắn trên cạn
	else if (_enviroment == Land)
	{
		//Khi di chuyển hướng và hướng súng bình thường
		if (_physical.vx != 0 && _gun_direction == Normal)
		{
			_current_sprite = _bill_move;
			_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 5, 9);
		}
		else
		{
			//Khi đứng yên 
			_current_sprite = _bill_stand;
			switch (_gun_direction)
			{
			case Normal:
				_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 0, 1);
				break;
			case Up:
				_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 2, 3);
				break;
			case Down:
				_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 4, 4);
				break;
			}
		}
	}
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
	//Vẽ dưới nước
	if (_enviroment == Water)
	{
		_current_sprite = _bill_in_water;
		switch (_gun_direction)
		{
		case Normal:
			_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 1, 1);
			break;
		case Down:
			_current_sprite->DrawWithDirecion(pos, _physical.vx_last, 0, 0);
			break;
		}
	}
	//Vẽ trên cạn
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


