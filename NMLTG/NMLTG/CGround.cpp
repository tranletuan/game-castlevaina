#include "CGround.h"

CGround::CGround(int id, SpecificType specific_type, D3DXVECTOR3 pos)
	:CObject(id, specific_type, Ground, pos)
{
}

CGround::~CGround()
{
	if (_current_sprite != NULL)
	{
		delete _current_sprite;
	}
}

void CGround::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	switch (_specific_type)
	{
	case Ground1:
		_current_sprite = new CSprite(rs->_ground_1);
		break;
	case Ground2:
		_current_sprite = new CSprite(rs->_ground_2);
		break;
	case Ground3:
		_current_sprite = new CSprite(rs->_ground_3);
		break;
	}

	_physical.SetBounds(
		_physical.x,
		_physical.y,
		_current_sprite->sprite_texture->frame_width,
		_current_sprite->sprite_texture->frame_height
		);	
}

void CGround::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	_current_sprite->PerformAllEffect(GROUND_TIME_EFFECT);
	_current_sprite->Draw(pos.x, pos.y);
}