#include "CBoss1.h"

CBoss1::CBoss1(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, pos, width, height)
{
	_hp = 3;
	_state = B1S_Acti;
	_destroy_bg = false;
	_time_counter = 0;
	LoadResources();
}



void CBoss1::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_sprite_bg = new CSprite(rs->_boss1_bg);
	_sprite_badge = new CSprite(rs->_boss1_badge);
	_sprite_effect = new CSprite(rs->_effect_destroy);
	_sprite_effect1 = new CSprite(rs->_effect_destroy);
	_sprite_effect2 = new CSprite(rs->_effect_destroy);
	_sprite_effect3 = new CSprite(rs->_effect_destroy);
	_sprite_effect4 = new CSprite(rs->_effect_destroy);
}

void CBoss1::Draw()
{
	CCamera *cam = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = cam->Transform(_physical.x, _physical.y);

	switch (_state)
	{
	case B1S_DieBadge:
		DrawWhenBadgeDie(pos);
		break;
	case B1S_DestroyBG1:
		DrawWhenDestroyBG1(pos);
		break;
	case B1S_DestroyBG2:
		DrawWhenDestroyBG2(pos);
		break;
	case B1S_DestroyBG3:
		DrawWhenDestroyBG3(pos);
		break;
	case B1S_DestroyBG4:
		DrawWhenDestroyBG4(pos);
		break;
	case B1S_Acti:
		DrawWhenActi(pos);
		break;
	case B1S_NextMap:
		DrawWhenNextMap(pos);
		break;
	default:
		break;
	}
}

void CBoss1::Update(int delta_time)
{
	switch (_state)
	{
	case B1S_DieBadge:
		if (_destroy_bg)
		{
			_state = B1S_DestroyBG1;
		}
		break;
	case B1S_DestroyBG1:
		_time_counter += delta_time;
		if ((_time_counter / 600) > 0)
		{
			_state = B1S_DestroyBG2;
		}
		break;
	case B1S_DestroyBG2:
		_time_counter += delta_time;
		if ((_time_counter / 600) > 1)
		{
			_state = B1S_DestroyBG3;
		}
		break;
	case B1S_DestroyBG3:
		_time_counter += delta_time;
		if ((_time_counter / 600) > 2)
		{
			_state = B1S_DestroyBG4;
		}
		break;
	case B1S_DestroyBG4:
		_time_counter += delta_time;
		if ((_time_counter / 600) > 3)
		{
			_state = B1S_NextMap;
		}
		break;
	case B1S_Acti:
		if (_hp == 0)
		{
			_state = B1S_DieBadge;
		}
		break;
	case B1S_NextMap:
		break;
	default:
		break;
	}
}

void CBoss1::DrawWhenActi(D3DXVECTOR3 pos)
{
	_sprite_bg->SelectFrameOf(0);
	_sprite_bg->Draw(pos.x, pos.y);
	D3DXVECTOR3 pos_badge = D3DXVECTOR3(pos.x - BOSS1_SPACE_X, pos.y + BOSS1_SPACE_Y, 0);
	_sprite_badge->DrawWithDirection(pos_badge, 1, 0, 2, 200);

}

void CBoss1::DrawWhenBadgeDie(D3DXVECTOR3 pos)
{
	_sprite_bg->SelectFrameOf(0);
	_sprite_bg->Draw(pos.x, pos.y);
	D3DXVECTOR3 pos_badge = D3DXVECTOR3(pos.x - BOSS1_SPACE_X, pos.y + BOSS1_SPACE_Y, 0);
	_sprite_badge->SelectFrameOf(0);
	_sprite_badge->Draw(pos_badge.x, pos_badge.y);
	if (_sprite_effect->DrawWithDirectionAndOneTimeEffect(pos_badge, 1, 0, 2, 300))
	{
		_destroy_bg = true;
	}
}

void CBoss1::DrawWhenDestroyBG1(D3DXVECTOR3 pos)
{
	_sprite_bg->DrawWithDirectionAndOneTimeEffect(pos, 1, 0, 1, 100);
	D3DXVECTOR3 pos_draw = D3DXVECTOR3(pos.x - BOSS1_SPACE_DESTROY_X, pos.y + 30, 0);
	D3DXVECTOR3 pos_draw1 = D3DXVECTOR3(pos.x - BOSS1_SPACE_DESTROY_X, pos.y + 30 + BOSS1_SPACE_DESTROY_Y, 0);
	_sprite_effect1->DrawWithDirectionAndOneTimeEffect(pos_draw, 1, 0, 2, 300);
	_sprite_effect1->DrawWithDirectionAndOneTimeEffect(pos_draw1, 1, 0, 2, 300);
}
void CBoss1::DrawWhenDestroyBG2(D3DXVECTOR3 pos)
{
	_sprite_bg->SelectFrameOf(1);
	_sprite_bg->Draw(pos.x, pos.y);
	D3DXVECTOR3 pos_draw = D3DXVECTOR3(pos.x + BOSS1_SPACE_DESTROY_X, pos.y + 30, 0);
	D3DXVECTOR3 pos_draw1 = D3DXVECTOR3(pos.x + BOSS1_SPACE_DESTROY_X, pos.y + 30 + BOSS1_SPACE_DESTROY_Y, 0);
	_sprite_effect2->DrawWithDirectionAndOneTimeEffect(pos_draw, 1, 0, 2, 300);
	_sprite_effect2->DrawWithDirectionAndOneTimeEffect(pos_draw1, 1, 0, 2, 300);
}
void CBoss1::DrawWhenDestroyBG3(D3DXVECTOR3 pos)
{
	_sprite_bg->SelectFrameOf(1);
	_sprite_bg->Draw(pos.x, pos.y);
	D3DXVECTOR3 pos_draw = D3DXVECTOR3(pos.x + 2 * BOSS1_SPACE_DESTROY_X, pos.y + 30, 0);
	D3DXVECTOR3 pos_draw1 = D3DXVECTOR3(pos.x + 2 * BOSS1_SPACE_DESTROY_X, pos.y + 30 + BOSS1_SPACE_DESTROY_Y, 0);
	_sprite_effect3->DrawWithDirectionAndOneTimeEffect(pos_draw, 1, 0, 2, 300);
	_sprite_effect3->DrawWithDirectionAndOneTimeEffect(pos_draw1, 1, 0, 2, 300);
}
void CBoss1::DrawWhenDestroyBG4(D3DXVECTOR3 pos)
{
	_sprite_bg->SelectFrameOf(1);
	_sprite_bg->Draw(pos.x, pos.y);
	D3DXVECTOR3 pos_draw = D3DXVECTOR3(pos.x + 3 * BOSS1_SPACE_DESTROY_X, pos.y + 30, 0);
	D3DXVECTOR3 pos_draw1 = D3DXVECTOR3(pos.x + 3 * BOSS1_SPACE_DESTROY_X, pos.y + 30 + BOSS1_SPACE_DESTROY_Y, 0);
	_sprite_effect4->DrawWithDirectionAndOneTimeEffect(pos_draw, 1, 0, 2, 300);
	_sprite_effect4->DrawWithDirectionAndOneTimeEffect(pos_draw1, 1, 0, 2, 300);
}

void CBoss1::DrawWhenNextMap(D3DXVECTOR3 pos)
{
	_sprite_bg->SelectFrameOf(1);
	_sprite_bg->Draw(pos.x, pos.y);
}

CBoss1::~CBoss1()
{

}