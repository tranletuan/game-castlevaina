#include "CRunman.h"

CRunman::CRunman(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, pos, width, height)
{
	LoadResources();
}

CRunman::~CRunman()
{
}

void CRunman::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	if (_specific_type == RunMan)
	{
		_live_sprite = new CSprite(rs->_enemy_run_man);
		_die_sprite = new CSprite(rs->_effect_die);
		_current_sprite = _live_sprite;
	}
}

void CRunman::Update(int delta_time)
{
	if (_hp == 0)
	{
		if (_physical.current_vy >= 0)
		{
			_physical.vx = 0.02f;
			_physical.vy = ENEMY_VY_DIE;
			_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
		}
		//Khi đạt độ cao cực đại thì trạng thái chuyển sang die
		else
		{
			SetStatus(RMDie);
		}
	}
	else
	{
		_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
		_physical.SetBounds(_physical.x, _physical.y, ENEMY_RUN_MAN_BOUNDS_WIDTH, ENEMY_RUN_MAN_BOUNDS_HEIGHT);
	}
}

void CRunman::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);
	
	switch (_rm_status)
	{
	case RMStand:
		DrawWhenStand(pos);
		break;
	case RMRun:
		DrawWhenRun(pos);
		break;
	case RMAttack:
		DrawWhenAttack(pos);
		break;
	case RMJump:
		DrawWhenJump(pos);
		break;
	case RMDie:
		DrawWhenDie(pos);
		break;
	}
}

void CRunman::SetTarget(D3DXVECTOR3 pos, D3DXVECTOR3 target)
{
	_physical.x = pos.x;
	_physical.y = pos.y;
	_physical.n = 0;
	_hp = 1;
	_rm_status = RMRun;

	if (pos.x < target.x)
	{
		_physical.vx_last = 1;
		_physical.vx = ENEMY_RUN_MAN_VX;
	}
	else
	{
		_physical.vx_last = -1;
		_physical.vx = -ENEMY_RUN_MAN_VX;
	}
}

void CRunman::DrawWhenStand(D3DXVECTOR3 pos)
{
	if (_current_sprite->index != 7)
	{
		_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 6, 7, 150);
	}
}

void CRunman::DrawWhenRun(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 2);
}

void CRunman::DrawWhenAttack(D3DXVECTOR3 pos)
{
}

void CRunman::DrawWhenJump(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 3, 5);
}

void CRunman::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _die_sprite;
	if (_current_sprite->index != _current_sprite->sprite_texture->count - 1)
	{
		_current_sprite->DrawWithDirection(pos, _physical.vx_last, 0, 2);
	}
}

bool CRunman::SetStatus(RMStatus status)
{
	if (_rm_status < status)
	{
		_rm_status = status;
		return true;
	}

	return false;
}

bool CRunman::Jumping()
{
	if (!SetStatus(RMJump)) return false;

	//Nếu chuyển thành công thì thực hiện nhảy
	float rate = rand() % 10 / (float)10;
	_physical.vy = ENEMY_RUN_MAN_VY + rate;
	_physical.n = 0;

	return true;
}

void CRunman::Standing(float y_ground, SpecificType ground_type)
{
	if (_physical.n == 0)
	{
		if (_hp > 0)
		{
			if (ground_type == Ground_Water)
			{
				_rm_status = RMStand;
				_physical.SetBounds(0, 0, 0, 0);
			}
			else
			{
				_rm_status = RMRun;
			}
		}

		_physical.vy = 0;
	}

	//Chạm đất thì vector phản lực n phải có 1 lực tương đương với vector trọng trường
	_physical.n = GRAVITY;
	_physical.time_in_space = GetTickCount();
	_physical.y = y_ground;
}