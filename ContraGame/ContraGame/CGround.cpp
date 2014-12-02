#include "CGround.h"

CGround::CGround(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Ground, pos, width, height)
{
	_count = width / GROUND_SIZE_NORMAL;
	_time_count = 0;
	_isDraw = false;
	LoadResources();
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
	case Ground_Grass:
		_current_sprite = new CSprite(rs->_ground_grass);
		break;
	case Ground_Water:
		_current_sprite = new CSprite(rs->_ground_water);
		break;
	case Ground_Effect:
		_current_sprite = new CSprite(rs->_ground_effect1);
		break;
	}
}

void CGround::Update(int delta_time)
{

	
}

void CGround::Draw()
{
	

}