#include "CGround.h"

CGround::CGround(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Ground, pos, width, height)
{
	_count = width / GROUND_SIZE_NORMAL;
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
	case Ground3:
		_current_sprite = new CSprite(rs->_ground_3);
		break;
	}
}

void CGround::Update(float delta_time)
{

}

void CGround::Draw()
{
	//Chỉ vẽ để kiểm tra, khi chạy game đoạn code sẽ bị xóa
	int x = _physical.bounds.left + GROUND_SIZE_NORMAL / 2;

	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(x, _physical.y);

	_current_sprite->PerformAllEffect(GROUND_TIME_EFFECT);
	for (int i = 0; i < _count; i++)
	{
		_current_sprite->Draw(pos.x, pos.y);
		pos.x += GROUND_SIZE_NORMAL;
	}
}