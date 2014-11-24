#include "CItemStand.h"

CItemStand::CItemStand(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, pos, width, height)
{
	_hp = 1;
	LoadResources();
}

void CItemStand::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();	
	_sprite_effect = new CSprite(rs->_effect_destroy);
	_sprite_item = new CSprite(rs->_item);
	_sprite_stand = new CSprite(rs->_item_stand);

	switch (_specific_type)
	{
	case ItemM_Stand:
		_pos_stand = D3DXVECTOR3(_physical.x, _physical.y, 0);
		_sprite_item->SelectFrameOf(1);
		break;
	default:
		break;
	}
	CCamera *_cam = CResourcesManager::GetInstance()->_camera;
	_pos_stand = _cam->Transform(_pos_stand.x, _pos_stand.y);

}

void CItemStand::Draw()
{
	CCamera *_cam = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = _cam->Transform(_physical.x, _physical.y);
	// khi posX + width/2 < posX + width của camera cho trương hợp hướng camera di chuyển ngang   
	if (_physical.x + _sprite_stand->sprite_texture->frame_width / 2 >= _cam->getPosX() + _cam->getWidth()
		&& _physical.y + _sprite_stand->sprite_texture->frame_height / 2 >= _cam->getPosY())
	{
		DrawWhenStand();
	}
	else
	{
		if (_hp > 0)
		{
			DrawWhenActivity();
		}
	}
	if (_hp == 0)
	{
		DrawWhenAttack(pos);
	}
}

void CItemStand::Update(int delta_time)
{
	if (_hp == 0 && _physical.current_vy >= 0)
	{
		_physical.vx = 0.01f;
		_physical.vy = ENEMY_VY_DIE;
		_physical.CalcPositionWithGravitation(delta_time, GRAVITY);
	}
}

void CItemStand::DrawWhenStand()
{
	// Khi chưa hoạt động chỉ ở index = 0;	
	_sprite_stand->DrawWithDirectionAndOneTimeEffect(_pos_stand, _physical.vx_last, 0, 0);
}

void CItemStand::DrawWhenActivity()
{
	// Khi hoạt động gán vô 1 animation cho nó
	_sprite_stand->DrawWithDirectionAndOneTimeEffect(_pos_stand, _physical.vx_last, 0, 7);
}

void CItemStand::DrawWhenAttack(D3DXVECTOR3 pos)
{
	// Khi bị bắt không vẽ _sprite_stand, _sprite_effect nổ theo _pos_stand , đồng thời vẻ _sprite_item vang lên
	_sprite_effect->DrawWithDirection(_pos_stand, _physical.vx_last, 0, 2);
	D3DXVECTOR2 pos2 = D3DXVECTOR2(pos.x, pos.y);
	_sprite_item->Draw(pos2);

}

CItemStand::~CItemStand()
{

}