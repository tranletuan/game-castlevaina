#include "CGroundWater.h"

CGroundWater::CGroundWater(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CGround(id, specific_type, pos, width, height)
{
	_count = width / GROUND_SIZE_NORMAL_X;
	_physical.y += 6;
	_physical.SetBounds(_physical.x, _physical.y, width, 4);
	LoadResources();
}

CGroundWater::~CGroundWater()
{

}

void CGroundWater::LoadResources()
{
	_current_sprite = new CSprite(CResourcesManager::GetInstance()->_ground_water);
}

void CGroundWater::Draw()
{
	//Chỉ vẽ để kiểm tra, khi chạy game đoạn code sẽ bị xóa
	//int x = _physical.bounds.left + GROUND_SIZE_NORMAL_X / 2;

	//CCamera* c = CResourcesManager::GetInstance()->_camera;
	//D3DXVECTOR3 pos = c->Transform(x, _physical.y - 6);

	////_current_sprite->PerformAllEffect(GROUND_TIME_EFFECT);
	//for (int i = 0; i < _count; i++)
	//{
	//	_current_sprite->Draw(pos.x, pos.y);
	//	pos.x += GROUND_SIZE_NORMAL_X;
	//}
}

void CGroundWater::Update(int delta_time)
{

}