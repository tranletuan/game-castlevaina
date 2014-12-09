#include "CItemFly.h"

CItemFly::CItemFly(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Item, pos, width, height)
{
	_hp = 1;
	_state_item_fly = SIF_Move;
	_physical.vx = ITEM_FLY_VX_MOVE;
	_angle = 0;
	LoadResources();
}

CItemFly::CItemFly(int id, SpecificType specific_type, D3DXVECTOR3 pos, TrackID track, int width, int height)
	:CObject(id, specific_type, pos, track, width, height)
{
	_hp = 1;
	_basic_type = Item;
	_state_item_fly = SIF_Move;
	if (_track == Track_LR)
	{
		_physical.vx = ITEM_FLY_VX_MOVE;
	}
	else if (_track == Track_RL)
	{
		_physical.vx = -ITEM_FLY_VX_MOVE;
	}
	else if (_track == Track_DU)
	{
		_physical.vy = ITEM_FLY_VX_MOVE;
	}
	else if (_track == Track_UD)
	{
		_physical.vy = -ITEM_FLY_VX_MOVE;
	}
	_angle = 0;
	LoadResources();
}

void CItemFly::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_sprite_effect = new CSprite(rs->_effect_destroy);
	_sprite_item = new CSprite(rs->_item);
	_current_sprite = new CSprite(rs->_item);
	_current_sprite->SelectFrameOf(0);
	switch (_specific_type)
	{
	case ItemM:
		_sprite_item->SelectFrameOf(1);
		break;
	case ItemB:
		_sprite_item->SelectFrameOf(2);
		break;
	case ItemF:
		_sprite_item->SelectFrameOf(3);
		break;
	case ItemS:
		_sprite_item->SelectFrameOf(4);
		break;
	case ItemL:
		_sprite_item->SelectFrameOf(5);
		break;
	case  ItemR:
		_sprite_item->SelectFrameOf(6);
		break;
	}

	
}

void CItemFly::Draw()
{
	if (_enable)
	{
		CCamera *_cam = CResourcesManager::GetInstance()->_camera;
		D3DXVECTOR3 pos = _cam->Transform(_physical.x, _physical.y);

		if (_hp == 0 && _pos_effect.x == 0 && _pos_effect.y == 0)
		{
			_pos_effect = _cam->Transform(_physical.x, _physical.y);
		}

		switch (_state_item_fly)
		{
		case SIF_Move:
			DrawWhenMove(pos);
			break;
		case SIF_Die:
			DrawWhenDie(pos);
			break;
		}
	}
}

void CItemFly::Update(int delta_time)
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_physical.SetBounds(
		_physical.x,
		_physical.y,
		_sprite_item->sprite_texture->frame_width,
		_sprite_item->sprite_texture->frame_height);

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
		vector<CObject*> grounds = rs->_grounds;
		for (vector<CObject*>::iterator i = grounds.begin(); i != grounds.end(); i++)
		{
			CObject* ground = (*i);
			if (ground->_specific_type == Ground_Grass)
			{
				CollisionDirection collision = NoCollision;
				collision = _physical.Collision(&ground->_physical);
				if (collision == TopCollision && _physical.current_vy < 0)
				{
					_physical.n = GRAVITY;
					_physical.y = ground->_physical.bounds.top + 2;
					_physical.vx = 0;
					_physical.vy = 0;
					break;
				}
			}
		}
		break;
	}

}

void CItemFly::MoveFollowCos(int delta_time)
{

	_angle += ITEM_FLY_ANGLE;
	if (_angle > 360) _angle = 360 - _angle;

	if (_track == Track_LR || _track == Track_RL)
	{
		_physical.y += ITEM_FLY_BOUND_COS * cos(D3DXToRadian(_angle));
		_physical.vy = 0;
		_physical.CalcPositionWithoutGravitation(delta_time);
	}
	else
	{
		_physical.x += ITEM_FLY_BOUND_COS * cos(D3DXToRadian(_angle));
		_physical.vx = 0;
		_physical.CalcPositionWithoutGravitation(delta_time);
	}



}

void CItemFly::MoveWhenDie(int delta_time)
{
	if (_hp == 0 && _physical.n == 0)
	{
		_physical.vx = ITEM_FLY_VX_DIE;
		_physical.vy = ITEM_FLY_VY_DIE;
		_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
	}
}

void CItemFly::DrawWhenMove(D3DXVECTOR3 pos)
{
	// Khi chưa hoạt động chỉ ở index = 0;	
	_current_sprite->Draw(pos.x, pos.y);
}

void CItemFly::DrawWhenDie(D3DXVECTOR3 pos)
{
	// Khi bị bắt không vẽ _sprite_stand, _sprite_effect nổ theo _pos_stand , đồng thời vẻ _sprite_item vang lên
	if (_sprite_effect->index != 2)
	{
		_sprite_effect->DrawWithDirectionAndOneTimeEffect(_pos_effect, _physical.vx_last, 0, 2, 200);
	}
	// Vẽ item văng lên	
	_sprite_item->Draw(pos.x, pos.y);
}

CItemFly::~CItemFly()
{

}