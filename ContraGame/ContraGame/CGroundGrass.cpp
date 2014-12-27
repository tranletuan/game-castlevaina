#include "CGroundGrass.h"

CGroundGrass::CGroundGrass(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CGround(id, specific_type, pos, width, height)
{
	_count = width / GROUND_SIZE_NORMAL_X;
	_physical.y += 6;
	_physical.SetBounds(_physical.x, _physical.y, width, 4);
	LoadResources();
}

CGroundGrass::~CGroundGrass()
{

}

void CGroundGrass::LoadResources()
{
	_current_sprite = new CSprite(CResourcesManager::GetInstance()->_ground_grass);
}

void CGroundGrass::Draw()
{
	//Chỉ vẽ để kiểm tra, khi chạy game đoạn code sẽ bị xóa
	int x = _physical.bounds.left + GROUND_SIZE_NORMAL_X / 2;

	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(x, _physical.y - 6);

	//_current_sprite->PerformAllEffect(GROUND_TIME_EFFECT);
	for (int i = 0; i < _count; i++)
	{
		_current_sprite->Draw(pos.x, pos.y);
		pos.x += GROUND_SIZE_NORMAL_X;
	}
}

void CGroundGrass::Update(int delta_time)
{

}