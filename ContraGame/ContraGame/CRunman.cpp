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

	if (_specific_type == RunMan || _specific_type == RunMan_Fire)
	{
		_live_sprite = new CSprite(rs->_enemy_run_man);
		_die_sprite = new CSprite(rs->_effect_die);
		_current_sprite = _live_sprite;
	}
}

void CRunman::Update(int delta_time)
{
	if (!_enable) return;

	if (_hp <= 0)
	{
		_physical.SetBounds(0, 0, 0, 0);
		if (_physical.n == 0 && _physical.current_vy <= 0)
		{
			SetStatus(RMDie);
		}
	}
	else
	{
		_physical.SetBounds(_physical.x, _physical.y, ENEMY_RUN_MAN_BOUNDS_WIDTH, ENEMY_RUN_MAN_BOUNDS_HEIGHT);
	}

	_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
}

void CRunman::Draw()
{
	if (_enable)
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
}

void CRunman::SetTarget(D3DXVECTOR3 pos, D3DXVECTOR3 target)
{
	_physical.x = pos.x;
	_physical.y = pos.y;
	_physical.vy = 0;
	_physical.n = 0;
	_physical.time_in_space = 0;
	_physical.SetBounds(_physical.x, _physical.y, ENEMY_RUN_MAN_BOUNDS_WIDTH, ENEMY_RUN_MAN_BOUNDS_HEIGHT);
	
	_hp = 1;
	_enable = true;
	_rm_status = RMRun;
	_can_impact = true;
	_die_sprite->Reset();
	_current_sprite = _live_sprite;

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
		pos.y += (ENEMY_RUN_MAN_BOUNDS_HEIGHT - 5);
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
	if (_current_sprite == _live_sprite && _current_sprite->index != 5)
	{
		_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 3, 5);
	}
	else
	{
		_current_sprite = _die_sprite;
		if (_current_sprite->index != 2)
		{
			_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, _physical.vx_last, 0, 2, 150);
		}
		else
		{
			_enable = false;
		}
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
	float vx = ENEMY_RUN_MAN_VX_JUMP + rand() % 3 / (float)100 + 0.01f;
	vx = _physical.vx_last > 0 ?  vx : -vx;
	_physical.vx = vx;
	_physical.vy = ENEMY_RUN_MAN_VY;
	_physical.n = 0;
	_physical.time_in_space = 0;
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
				_can_impact = false;
				_physical.SetBounds(0, 0, 0, 0);
			}
			else
			{
				_rm_status = RMRun;
				_physical.y = y_ground;
				_physical.vx = _physical.vx_last > 0 ? ENEMY_RUN_MAN_VX : -ENEMY_RUN_MAN_VX;
			}
		}

		_physical.vy = 0;
	}

	//Chạm đất thì vector phản lực n phải có 1 lực tương đương với vector trọng trường
	_physical.n = GRAVITY;
	_physical.time_in_space = 0;
}

void CRunman::Dying()
{
	if (_hp <= 0)
	{
		_physical.vx = 0.02f;
		_physical.vy = ENEMY_VY_DIE;
		_physical.n = 0;
		_physical.SetBounds(0, 0, 0, 0);
		_physical.time_in_space = 0;
	}

}

