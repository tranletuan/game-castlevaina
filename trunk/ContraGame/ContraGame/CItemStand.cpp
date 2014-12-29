#include "CItemStand.h"

CItemStand::CItemStand(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Item, pos, width, height)
{
	_hp = 1;
	LoadResources();
	_state_item_stand = SIS_Close;
	_physical.SetBounds(pos.x, pos.y, 20, 20);
	_enable = true;
	_pos_stand = pos;
}

void CItemStand::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();	
	_sprite_effect = new CSprite(rs->_effect_destroy);
	_sprite_item = new CSprite(rs->_item);
	_sprite_stand = new CSprite(rs->_item_stand);

	// lấy index của _sprite_item cho mỗi loại đạn
	switch (_specific_type)
	{
	case ItemM_Stand:		
		_sprite_item->SelectFrameOf(1);
		break;
	case ItemS_Stand:
		_sprite_item->SelectFrameOf(4);
		break;
	case ItemF_Stand:
		_sprite_item->SelectFrameOf(3);
		break;
	case ItemB_Stand:
		_sprite_item->SelectFrameOf(2);
		break;
	case ItemL_Stand:
		_sprite_item->SelectFrameOf(5);
		break;
	}
}

void CItemStand::Draw()
{
	CCamera *_cam = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos;

	if (_hp <= 0)
	{
		pos = _cam->Transform(_physical.x, _physical.y);;
	}
	else
	{
		pos = _cam->Transform(_pos_stand.x, _pos_stand.y);
	}

	// Xử lý vẽ theo state item
	switch (_state_item_stand)
	{
	case SIS_Close:
		DrawWhenStand(pos);
		break;
	case SIS_Open:
	case SIS_Enable:
		DrawWhenActivity(pos);
		break;
	case SIS_Spatter:
	case SIS_EAT:
		DrawWhenAttack(pos);
		break;
	}
}

void CItemStand::Update(int delta_time)
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	CCamera *_cam = rs->_camera;
	int curMap = rs->m_curMap;
	// chuyển state item
	// Xét khoảng hoạt động của item stand the o level map
	if (_state_item_stand == SIS_Close || _state_item_stand == SIS_Open)
	{
		switch (curMap)
		{
		case 1:
		case 3:
			if (_physical.x + _sprite_stand->sprite_texture->frame_width / 2 < _cam->getPosX() + _cam->getWidth() &&
				_physical.x - _sprite_stand->sprite_texture->frame_width / 2 > _cam->getPosX())
			{
				_state_item_stand = SIS_Open;
			}
			else
			{
				_state_item_stand = SIS_Close;
			}
			break;
		case 2:
			if (_physical.y + _sprite_stand->sprite_texture->frame_height / 2 < _cam->getPosY()
				&& _physical.y - _sprite_stand->sprite_texture->frame_height / 2 > 0)
			{
				_state_item_stand = SIS_Open;
			}
			else
			{
				_state_item_stand = SIS_Close;
			}
			break;
		}
	}

	if (_state_item_stand == SIS_Open)
	{
		if (_sprite_stand->index > 3 && _hp > 0)
		{
			_state_item_stand = SIS_Enable;
		}
	}

	if (_state_item_stand == SIS_Enable)
	{
		if (_sprite_stand->index <= 3 && _hp > 0)
		{
			_state_item_stand = SIS_Open;
		}
	}
	

	// set vx & vy item văng lên
	if (_hp == 0 && _physical.n == 0)
	{
		_state_item_stand = SIS_Spatter;
		_physical.vx = ITEM_STAND_VX_ENABLE;
		_physical.vy = ITEM_STAND_VY_ENABLE;		
		_physical.CalcPositionWithGravitation(delta_time, GRAVITY);			
	}

	switch (_state_item_stand)
	{
	case SIS_Close:
	case SIS_Open:
		_can_impact = false;
		break;
	case SIS_EAT:
	case SIS_Enable:
		_can_impact = true;
		break;
	case SIS_Spatter:
		_physical.SetBounds(_physical.x, _physical.y, 20, 20);
		_can_impact = true;
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
					_state_item_stand = SIS_EAT;
					_physical.SetBounds(_physical.x, _physical.y, 20, 30);
					break;
				}
			}
		}
		break;
	}
}

void CItemStand::DrawWhenStand(D3DXVECTOR3 pos)
{
	// Khi chưa hoạt động chỉ ở index = 0;	
	_sprite_stand->SelectFrameOf(0);
	_sprite_stand->Draw(pos.x, pos.y);
}

void CItemStand::DrawWhenActivity(D3DXVECTOR3 pos)
{
	// Khi hoạt động gán vô 1 animation cho nó
	_sprite_stand->DrawWithDirection(pos, _physical.vx_last, 0, 9, 200);
}

void CItemStand::DrawWhenAttack(D3DXVECTOR3 pos)
{	
	// Khi bị bắt không vẽ _sprite_stand, _sprite_effect nổ theo _pos_stand , đồng thời vẻ _sprite_item văng lên
	if (_sprite_effect->index != 2)
	{
		D3DXVECTOR3 pos_stand = CResourcesManager::GetInstance()->_camera->Transform(_pos_stand.x, _pos_stand.y);
		_sprite_effect->DrawWithDirectionAndOneTimeEffect(pos_stand, _physical.vx_last, 0, 2, 200);
	}

	// Vẽ item văng lên	
	if (_physical.bounds.left != 0 && _physical.bounds.top != 0 &&
		_physical.bounds.right != 0 && _physical.bounds.bottom != 0 && _enable)
	{
		_sprite_item->Draw(pos.x, pos.y);
	}
}

CItemStand::~CItemStand()
{

}