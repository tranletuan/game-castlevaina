#include "CWaterFall.h"

CWaterFall::CWaterFall(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CGround(id, specific_type, pos, width, height)
{
	_basic_type = Effect;
	_cols = width / GROUND_SIZE_NORMAL_X;
	_rows = height / GROUND_SIZE_NORMAL_Y;
	_countTime = 0;
	LoadResources();
}

void CWaterFall::LoadResources()
{
	_current_sprite = new CSprite(CResourcesManager::GetInstance()->_ground_waterfall);
}

void CWaterFall::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	for (int i = 0; i < _cols; i++)
	{
		for (int j = 0; j < _rows; j++)
		{
			float x = GROUND_SIZE_NORMAL_X*i + GROUND_SIZE_NORMAL_X / 2 + _physical.bounds.left;
			float y = GROUND_SIZE_NORMAL_Y*j + GROUND_SIZE_NORMAL_Y / 2 + _physical.bounds.bottom;
			D3DXVECTOR3 pos = c->Transform(x, y);			
			if (_countTime % 30 > 15 && _countTime % 30 < 30)
			{
				if (j % 2 == 0)
				{
					_current_sprite->SelectFrameOf(0);
				}
				else
				{
					_current_sprite->SelectFrameOf(1);
				}				
			}
			else
			{
				if (j % 2 == 0)
				{
					_current_sprite->SelectFrameOf(1);
				}
				else
				{
					_current_sprite->SelectFrameOf(0);
				}
			}
			_current_sprite->Draw(pos.x, pos.y);
		}
	}
}

void CWaterFall::Update(int delta_time)
{
	_countTime++;
	if (_countTime > 5000)
	{
		_countTime = 0;
	}
}

CWaterFall::~CWaterFall()
{

}