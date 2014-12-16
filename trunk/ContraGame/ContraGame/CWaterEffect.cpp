#include "CWaterEffect.h"

CWaterEffect::CWaterEffect(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEffectObject(id, specific_type, pos, width, height)

{
	_count = width / GROUND_SIZE_NORMAL_X;
	_time_count = 0;
	_isDraw = false;
	LoadResources();
}

CWaterEffect::~CWaterEffect()
{
	if (_current_sprite != NULL)
	{
		delete _current_sprite;
	}
}

void CWaterEffect::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_current_sprite = new CSprite(rs->_effect_water);

}

void CWaterEffect::Update(int delta_time)
{
	_time_count++;
	_isDraw = false;
	if (_time_count > 10000)
	{
		_time_count = 0;
	}
	if (_time_count % 20 > 5 && _time_count % 20 < 20)
	{
		_isDraw = true;
	}
}

void CWaterEffect::Draw()
{
	if (_isDraw)
	{
		//Chỉ vẽ để kiểm tra, khi chạy game đoạn code sẽ bị xóa
		int x = _physical.bounds.left + GROUND_SIZE_NORMAL_X / 2;

		CCamera* c = CResourcesManager::GetInstance()->_camera;
		D3DXVECTOR3 pos = c->Transform(x, _physical.y);

		for (int i = 0; i < _count; i++)
		{
			_current_sprite->Draw(pos.x, pos.y);
			pos.x += GROUND_SIZE_NORMAL_X;
		}
	}

}