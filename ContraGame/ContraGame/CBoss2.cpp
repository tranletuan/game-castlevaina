#include "CBoss2.h"

CBoss2::CBoss2(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, pos, width, height)
{
	_hp = 15;
	_status = B2Wait;
	_left_arm = new CBoss2Arm(0, Boss2_Arm, D3DXVECTOR3(pos.x - 52, pos.y + 34, 0), 0, 0, -1);
	_right_arm = new CBoss2Arm(1, Boss2_Arm, D3DXVECTOR3(pos.x + 52, pos.y + 34, 0), 0, 0, 1);
	LoadResources();
}

CBoss2::~CBoss2()
{
}

void CBoss2::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_live_sprite = new CSprite(rs->_boss2_live);
	_die_sprite = new CSprite(rs->_boss2_die);
	_destroy_sprite = new CSprite(rs->_effect_destroy);
	_current_sprite = _live_sprite;
}

void CBoss2::Update(int time)
{
	if (_hp > 0)
	{
	}
}

void CBoss2::Draw()
{
	if (_enable)
	{
		CCamera* c = CResourcesManager::GetInstance()->_camera;
		D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

		switch (_status)
		{
		case B2Prepare:
			DrawWhenPrepare(pos);
			break;
		case B2Wait:
			DrawWhenWait(pos);
			break;
		case B2Attack:
			DrawWhenAttack(pos);
			break;
		case B2Die:
			DrawWhenDie(pos);
			break;
		}
	}
}

vector<CPhysical> CBoss2::GetListElement()
{

	vector<CPhysical> list;
	return list;
}

void CBoss2::DrawWhenPrepare(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 2, 600);
}

void CBoss2::DrawWhenWait(D3DXVECTOR3 pos)
{
	
}

void CBoss2::DrawWhenAttack(D3DXVECTOR3 pos)
{

}

void CBoss2::DrawWhenDie(D3DXVECTOR3 pos)
{
	_current_sprite = _die_sprite;
	_current_sprite->Draw(pos.x, pos.y);
}

void CBoss2::Attacking()
{
}