#include "CItemFly.h"

CItemFly::CItemFly(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, pos, width, height)
{
	_hp = 1;
	_state_item_fly = SIF_Move;
	_posY_center = pos.y;
	LoadResources();
}

void CItemFly::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_sprite_effect = new CSprite(rs->_effect_destroy);
	_sprite_item = new CSprite(rs->_item);
	_sprite_item->SelectFrameOf(0);
}

void CItemFly::Draw()
{
	CCamera *_cam = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos;

	// lấy tọa độ effect nổ
	if (_hp == 0)
	{
		_pos_effect = _cam->Transform(_physical.x, _physical.y);
		_hp--;
	}
	else
	{
		pos = _cam->Transform(_physical.x, _physical.y);
	}

	switch (_state_item_fly)
	{
	case SIF_Move:
		DrawWhenMove(pos);
		break;
	case SIF_Die:
		DrawWhenDie(pos);
		break;
	default:
		break;
	}
}

void CItemFly::Update(int delta_time)
{
	if (_hp == 0)
	{
		_state_item_fly = SIF_Die;
	}
	switch (_state_item_fly)
	{
	case SIF_Move:		
		MoveFollowCos(delta_time);			
		break;
	case SIF_Die:
		MoveWhenDie(delta_time);
		break;
	default:
		break;
	}
	
}

void CItemFly::MoveFollowCos(int delta_time)
{
	_physical.vx = ITEM_FLY_VX_MOVE;
	_physical.current_vx = _physical.vx * delta_time;
	_physical.x += _physical.current_vx;

	// Để trách trường hợp vật di chuyển quá nhanh ảnh hưởng đến viêc vẽ
	// giảm số lần cập nhật tọa độ Y
	_counter++;
	_time_counter += ITEM_FLY_ANGLE;
	_physical.vy = 0;
	if (_counter % 3 == 0)
	{
		_physical.current_vy = ITEM_FLY_BOUND_COS * (cos(_time_counter));
	}	
	else
	{
		_physical.current_vy = 0;
	}
	_physical.y += _physical.current_vy;

}

void CItemFly::MoveWhenDie(int delta_time)
{	
	_physical.vx = ITEM_FLY_VX_DIE;
	_physical.vy = ITEM_FLY_VY_DIE;
	_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
}

void CItemFly::DrawWhenMove(D3DXVECTOR3 pos)
{
	// Khi chưa hoạt động chỉ ở index = 0;	
	_sprite_item->Draw(pos.x, pos.y);	
}
void CItemFly::DrawWhenDie(D3DXVECTOR3 pos)
{
	// Khi bị bắt không vẽ _sprite_stand, _sprite_effect nổ theo _pos_stand , đồng thời vẻ _sprite_item vang lên
	if (_sprite_effect->index != 2)
	{
		_sprite_effect->DrawWithDirectionAndOneTimeEffect(_pos_effect, _physical.vx_last, 0, 2, 200);
	}

	switch (_specific_type)
	{
	case ItemM:
		_sprite_item->SelectFrameOf(1);
		break;
	default:
		break;
	}

	// Vẽ item văng lên	
	_sprite_item->Draw(pos.x, pos.y);
}

CItemFly::~CItemFly()
{

}