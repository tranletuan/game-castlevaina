#include "CBill.h"

CBill::CBill(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Player, pos, width, height)
{
	_physical.vx_last = 1;
	_enviroment = Land;
	_gun_direction = Normal;
	_player_status = Fall;
	_physical.time_in_space = 0;
	_physical.vx = 0;
	_id_ground_stand = -1;
}

CBill::CBill()
{
	_physical.vx_last = 1;
	_enviroment = Land;
	_gun_direction = Normal;
	_player_status = Fall;
	_physical.time_in_space = 0;
	_physical.vx = 0;
	_id_ground_stand = -1;

	LoadResources();
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
	CResourcesManager* rs = CResourcesManager::GetInstance();

	_bill_stand = new CSprite(rs->_bill_stand);
	_bill_jump = new CSprite(rs->_bill_jump);
	_bill_die = new CSprite(rs->_bill_die);
	_bill_move = new CSprite(rs->_bill_move);
	_bill_in_water = new CSprite(rs->_bill_in_water);

	_current_sprite = _bill_stand;

	// postion
	_physical.x = rs->m_posBill.x;
	_physical.y = rs->m_posBill.y;

	// input
	_input = rs->m_input;
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
	case Attack:
		DrawWhenAttack(pos);
		break;
	case Fall:
		_current_sprite = _bill_move;
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 0);
		break;
	}


}

void CBill::Update(int delta_time)
{
	_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
	UpdateBounds();

	//Tự động cập nhật trạng thái rơi khi vật k chạm đất
	if (_player_status != Jump && _physical.n == 0)
	{
		SetStatus(Fall);
	}
}

bool CBill::SetStatus(PlayerStatus status)
{
	if (status >= _player_status)
	{
		_player_status = status;
		return true;
	}

	return false;
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
	//Kiểm tra trạng thái chuyển thành công hay không
	if (!SetStatus(Die)) return;

	int sign = _physical.vx_last > 0 ? -1 : 1;
	_physical.vx = BILL_VX * sign;
	_physical.vy = BILL_VY_DIE;
}

bool CBill::Falling(CObject* ground)
{
	//Trước khi rơi kiểm tra xem có khả năng tiếp đất hay không
	if (_physical.x >= ground->_physical.bounds.left &&
		_physical.x <= ground->_physical.bounds.right &&
		_id_ground_stand != ground->_id &&
		_physical.y - BILL_BOUNDS_HEIGHT / 2 - 1 > ground->_physical.bounds.top)
	{
		//Nếu có khả năng tiếp đất, kiểm tra trạng thái hiện tại 
		if (_player_status == Fall || _player_status == Jump) return false;
		if (!SetStatus(Fall)) return false;

		//Đã chuyển được trạng thái, bắt đầu rơi
		_physical.vx = 0;
		_physical.time_in_space = GetTickCount();
		return true;
	}

	return false;
}

void CBill::Jumping()
{
	//Kiểm tra trạng thái Jump có chuyển thành công hay không
	if (_enviroment == Water) return; //K được nhảy khi ở môi trường nước
	if (!SetStatus(Jump)) return;

	//Nếu chuyển thành công thì thực hiện nhảy
	_physical.vy = BILL_VY;
}

void CBill::Attacking()
{
	//Hàm này chủ yếu để tính toán góc bắn của player
	//k đưa các thông số constant vào config.h vì quá nhiều quá đặc biệt
	SetStatus(Attack);
	//Không bắn khi trạng thái nhân vật là Die
	if (_player_status == Die) return;

	D3DXVECTOR3 pos;
	int angle = 0;
	float x = _physical.vx_last > 0 ? _physical.x + 12 : _physical.x - 12;
	float y = 0;

	//Góc, và tọa độ đầu tiên của đạn bay ra tùy thuộc vào hướng bắn 
	switch (_gun_direction)
	{
	case Normal:
		if (_enviroment == Land)
			y = _physical.y + 1;
		else
			y = _physical.y - 8;

		angle = _physical.vx_last > 0 ? angle : angle + 180;
		break;
	case Up:
		if (_physical.vx != 0)
		{
			if (_enviroment == Land)
				y = _physical.y + 19;
			else
				y = _physical.y + 6;

			angle = 45;
			angle = _physical.vx_last > 0 ? angle : 180 - angle;
		}
		else
		{
			if (_weapon->GetWeaponType() == WPF)
				x = _physical.vx_last > 0 ? _physical.x - 10 : _physical.x - 18;
			else
				x = _physical.vx_last > 0 ? _physical.x + 4 : _physical.x - 2;

			y = _physical.y + _current_sprite->sprite_texture->frame_height / 2;
			angle = 90;
		}
		break;
	case Down:
		//Trong môi trường nước k bắn xuống
		if (_enviroment == Water) return;

		if (_physical.vx != 0)
		{
			y = _physical.y - 10;
			angle = -55;
			angle = _physical.vx_last > 0 ? angle : -180 - angle;
		}
		else
		{
			if (_player_status == Jump)
			{
				if (_weapon->GetWeaponType() == WPF)
					x = _physical.vx_last > 0 ? _physical.x - 10 : _physical.x - 18;
				else
					x = _physical.x;

				y = _physical.y - _current_sprite->sprite_texture->frame_height / 2;
				angle = -90;
			}
			else
			{
				y = _physical.y - 14;
				angle = _physical.vx_last > 0 ? 0 : 180;
			}
		}
		break;
	}

	pos = D3DXVECTOR3(x, y, 0);
	_weapon->Shooting(pos, angle, _physical.vx);
}

void CBill::Moving(float vx)
{
	SetStatus(Move);

	//Khi trạng thái hiện tại != die và fall mới được phép thay đổi vx
	if (_player_status != Die && _player_status != Fall)
	{
		//Ngoài trạng thái Die ra thì mọi trạng thái còn lại
		//đều cần set vx
		_physical.vx = vx;

		//K di chuyển và trạng thái != Jump thì chuyển trạng thái thành Stand
		if (vx == 0 && _player_status != Jump)
		{
			_player_status = Stand;
		}
		else if (vx != 0)
		{
			//Nếu ngược lại thì xác định hướng nhân vật đang đứng
			_physical.vx_last = vx;
		}
	}
}

void CBill::Standing(float y_ground, int id_ground)
{
	//y_ground là tọa độ mặt đất ở game world mà nhân vật tiếp xúc (ground->_physical.bounds.top + BILL_BOUNDS_HEIGHT / 2 + 1)
	//id_ground là id của mặt đất nhân vật đang tiếp xúc

	//Khi đang rơi mà va chạm mặt đất
	//n = 0 đồng nghĩa với đối tượng đang lơ lững trên không
	if (_physical.n == 0)
	{
		if (_player_status != Die)
		{
			_player_status = Stand;
		}

		//Khi tiếp đất tất cả mọi vận tốc đều bằng 0
		_physical.vx = 0;
		_physical.vy = 0;
	}

	//Chạm đất thì vector phản lực n phải có 1 lực tương đương với vector trọng trường
	_physical.n = GRAVITY;
	_physical.time_in_space = GetTickCount();
	_physical.y = y_ground;
	_id_ground_stand = id_ground;
}

//SUPPORT DRAW
void CBill::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _bill_die;
	_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 4);
}

void CBill::DrawWhenJump(D3DXVECTOR3 pos)
{
	_current_sprite = _bill_jump;
	_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 3);
}

void CBill::DrawWhenAttack(D3DXVECTOR3 pos)
{
	bool done = true;

	//Bắn dưới nước
	if (_enviroment == Water)
	{
		_current_sprite = _bill_in_water;
		switch (_gun_direction)
		{
		case Normal:
			done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 2, 2, 400);
			break;
		case Up:
			//Khi nhắm lên bắn có 2 kiểu, khi di chuyển hướng sung xéo
			//còn khi đứng yên hướng súng 90 độ
			if (_physical.vx != 0)
			{
				done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 3, 3, 400);
			}
			else
			{
				done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 4, 4, 400);
			}
			break;

		case Down:
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, 1, 1);
			break;
		}
	}
	//Bắn trên cạn
	else if (_enviroment == Land)
	{
		//Bắn khi di chuyển
		if (_physical.vx != 0)
		{
			_current_sprite = _bill_move;
			switch (_gun_direction)
			{
			case Normal:
				done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 5, 9);
				break;
			case Up:
				_current_sprite->DrawWithDirection(pos, _physical.vx_last, 10, 14);
				break;
			case Down:
				_current_sprite->DrawWithDirection(pos, _physical.vx_last, 15, 19);
				break;
			}
		}
		else
		{
			//Khi đứng yên 
			_current_sprite = _bill_stand;
			switch (_gun_direction)
			{
			case Normal:
				done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 1);
				break;
			case Up:
				if (_physical.vx == 0)
				{
					done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 2, 3);
				}
				break;
			case Down:
				_current_sprite->DrawWithDirection(pos, _physical.vx_last, 4, 4);
				break;
			}
		}
	}

	//Cờ hiệu bắn xong 1 viên đạn
	if (done)
	{
		if (_physical.vx == 0)
		{
			_player_status = Stand;
		}
		else
		{
			_player_status = Move;
		}
	}

}

void CBill::DrawWhenMove(D3DXVECTOR3 pos)
{
	if (_enviroment == Water)
	{
		_current_sprite = _bill_in_water;
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 1, 1);
	}
	else
	{
		_current_sprite = _bill_move;
		switch (_gun_direction)
		{
		case Normal:
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 4);
			break;
		case Up:
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, 10, 14);
			break;
		case Down:
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, 15, 19);
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
		case Up:
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, 1, 1);
			break;
		case Down:
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 0);
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
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 0);
			break;
		case Up:
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, 2, 2);
			break;
		case Down:
			_current_sprite->DrawWithDirection(pos, _physical.vx_last, 4, 4);
			break;
		}
	}
}

void CBill::UpdateBounds()
{
	//Khi ở trên cạn 
	if (_enviroment == Land)
	{
		switch (_player_status)
		{
		case Stand:
			if (_gun_direction == Down)
			{
				_physical.SetBounds(
					_physical.x,
					_physical.y - 20,
					34,
					16);
				break;
			}
		case Move:
		case Attack:
		case Fall:
			_physical.SetBounds(
				_physical.x,
				_physical.y,
				BILL_BOUNDS_WIDTH,
				BILL_BOUNDS_HEIGHT);
			break;
		case Jump:
		case Die:
			_physical.SetBounds(
				_physical.x,
				_physical.y,
				_current_sprite->sprite_texture->frame_width,
				_current_sprite->sprite_texture->frame_height);
			break;
		}
	}
	else //Khi ở dưới nước
	{
		_physical.SetBounds(
			_physical.x,
			_physical.y - 6,
			BILL_BOUNDS_WIDTH,
			16);
	}
}

int CBill::GetIdGroundIgnore()
{
	//Hàm này phục vụ cho xét va chạm, chỉ va chạm với 
	//mặt đất mà nhân vật k bỏ qua (hàm Falling)
	if (_player_status == Fall && _id_ground_stand >= 0)
	{
		return _id_ground_stand;
	}
	else
	{
		return -1;
	}
}

int CBill::GetGunDirection()
{
	return _gun_direction;
}

void CBill::ProcessInput()
{
	IsKeyDown();
	OnKeyDown();
	OnKeyUp();
}

void CBill::OnKeyDown()
{
	
	if (_input->KeyDown(DIK_L))
	{
		if (GetGunDirection() != Down)
		{
			Jumping();
		}
	}
	else if (_input->KeyDown(DIK_J))
	{
		Attacking();
	}
}

void CBill::OnKeyUp()
{
	//Ngừng di chuyển
	if (_input->onKeyUp(DIK_D) ||
		_input->onKeyUp(DIK_A))
	{
		Moving(0);
	} 
	//Hướng súng trở về bình thường
	else if (_input->onKeyUp(DIK_W) ||
		_input->onKeyUp(DIK_S))
	{
		SetGunDirection(Normal);
	}
}

void CBill::IsKeyDown()
{
	//Set phím di chuyển trái phải
	if (_input->KeyDown(DIK_D))
	{
		Moving(BILL_VX);
	}
	else if (_input->KeyDown(DIK_A))
	{
		Moving(-BILL_VX);
	}

	//Set phím hướng súng
	if (_input->KeyDown(DIK_W))
	{
		SetGunDirection(Up);
	}
	else if (_input->KeyDown(DIK_S))
	{
		SetGunDirection(Down);
	}
}