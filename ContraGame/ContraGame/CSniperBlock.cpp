#include "CSniperBlock.h"

CSniperBlock::CSniperBlock(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemyUseGun(id, specific_type, pos, width, height)
{
	_hp = 1;
	_physical.vx_last = -1;
	_can_impact = true;
	LoadResources();
}

CSniperBlock::~CSniperBlock()
{

}

void CSniperBlock::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	_live_sprite = new CSprite(rs->_enemy_sniper_block);
	_die_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _live_sprite;
	_max_bullet = 1;
}

void CSniperBlock::Draw()
{
	CEnemy::Draw();
}

void CSniperBlock::Update(int delta_time)
{
	//Target mục tiêu
	D3DXVECTOR3 pos_target = CResourcesManager::GetInstance()->m_posBill;
	SetTarget(pos_target.x, pos_target.y);

	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);

	//Khi hp = 0 cho lính nhảy lên
	if (_hp == 0 && _physical.current_vy >= 0)
	{
		_physical.SetBounds(0, 0, 0, 0);
		_enemy_status = EDie;
	
	}
}

void CSniperBlock::SetTarget(float x, float y)
{
	CEnemyUseGun::SetTarget(x, y);
	if (_target_angle >= 90 && _target_angle <= 270)
	{
		Attacking();
	}
	
}

void CSniperBlock::DrawWhenAttack(D3DXVECTOR3 pos)
{
	bool done = true;
	
	done = _current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 1);

	if (done == true)
	{
		_enemy_status = EWait;
	}
}

void CSniperBlock::DrawWhenWait(D3DXVECTOR3 pos)
{
	_current_sprite->SelectFrameOf(0);
	_current_sprite->Draw(pos.x,pos.y);
}

void CSniperBlock::DrawWhenDie(D3DXVECTOR3 pos)
{
	if (_die_sprite->index != 2)
	{
		_die_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 2, 200);
	}
	else
	{
		_enable = false;
	}
}

void CSniperBlock::Attacking()
{
	if (_hp == 0) return;
	if (!CheckTarget()) return; //Mục tiêu chưa vào tầm tấn công

	DWORD now = GetTickCount();

	//Giãn cách bắn 
	if (now - _last_time_shoot >= ENEMY_SNIPER_STAND_ELAPSED_SHOOT)
	{
		//Kiểm tra số đạn đã bắn, nếu vẫn còn bắn được thì bắn
		if (_queue_id_bullet.size() < _max_bullet)
		{
			//Chỉnh tọa độ bắn
			int x = _physical.x - 16;
			int y = _physical.y + 10;

			int id = _weapon->ShootingBulletME(D3DXVECTOR3(x, y, 0), 180, 0);

			if (id >= 0)
			{
				_queue_id_bullet.push(id);
			}

			_last_time_shoot = now;
			SetStatus(EAttack);
		}
	}
}