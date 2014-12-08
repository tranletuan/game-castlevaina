#include "CGroundStar.h"

CGroundStar::CGroundStar(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CGround(id, specific_type, pos, width, height)

{
	_basic_type = Effect;
	_count = width / GROUND_SIZE_NORMAL;
	_time_count = 0;
	_isDraw = false;
	_basic_type = Effect;
	_numSub = rand() % 10 + 10;
	
	LoadResources();
}

CGroundStar::~CGroundStar()
{
	if (_current_sprite != NULL)
	{
		delete _current_sprite;
	}
}

void CGroundStar::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	switch (_specific_type)
	{
		break;
	case Ground_Star:
		_current_sprite = new CSprite(rs->_ground_star);
		_current_sprite->SelectFrameOf(_indexSprite);
		break;
	}
}

void CGroundStar::Update(int delta_time)
{

	switch (_specific_type)
	{
	case Ground_Star:
		_time_count++;
		_isDraw = false;
		if (_time_count > 10000)
		{
			_time_count = 0;
		}
		if (_time_count % _numSub > 5 && _time_count % _numSub < 20)
		{
			_isDraw = true;
		}
		break;
	}
}

void CGroundStar::Draw()
{
	if (_isDraw)
	{

		//Chỉ vẽ để kiểm tra, khi chạy game đoạn code sẽ bị xóa
		int x = _physical.bounds.left + GROUND_SIZE_NORMAL / 2;

		CCamera* c = CResourcesManager::GetInstance()->_camera;
		D3DXVECTOR3 pos = c->Transform(x, _physical.y);

		for (int i = 0; i < _count; i++)
		{
			_current_sprite->Draw(pos.x, pos.y);
			pos.x += GROUND_SIZE_NORMAL;
		}
	}

}