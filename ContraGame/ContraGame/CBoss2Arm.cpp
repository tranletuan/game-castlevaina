#include "CBoss2Arm.h"

CBoss2Arm::CBoss2Arm(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Enemy, pos, width, height)
{
	_hp = 15;
	_last_time_change = 0;
	LoadResources();
}

CBoss2Arm::~CBoss2Arm()
{
}

void CBoss2Arm::LoadResources()
{
	int id = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(_physical.x, _physical.y, 0);
	for (int i = 0; i < 4; i++)
	{
		CBoss2Elbow* elbow = new CBoss2Elbow(id++, Boss2_Elbow, pos, 16, 16);
		elbow->LoadResources();
		_elbows[elbow->_id] = elbow;

		if (elbow->_id > 0)
		{
			elbow->_pre = _elbows[elbow->_id - 1];
			_elbows[elbow->_id - 1]->_next = elbow;
		}
	}
}

void CBoss2Arm::Update(int time)
{
	if (_elbows.size() > 0)
	{
		if (_hp > 0){
			//Random node nào sẽ là node chính
			if (_last_time_change == 0)
			{
				_last_time_change = GetTickCount();
			}

			DWORD  now = GetTickCount();
			if (now - _last_time_change >= BOSS2_ELAPSED_CHANGE)
			{
				_id_main_node = rand() % 3 + 1;

				//Tất cả các node đều phải ngừng hoạt động
				for (map<int, CBoss2Elbow*>::iterator i = _elbows.begin(); i != _elbows.end(); i++)
				{
					CBoss2Elbow* elbow = (*i).second;
					elbow->SetDeactivate();
				}

				int direction = _elbows[_id_main_node]->_physical.vx_last *-1;
				_elbows[_id_main_node]->SetActive(-1, direction);
				_last_time_change = 0;
			}
		}

		//Cập nhật từng node con
		for (map<int, CBoss2Elbow*>::iterator i = _elbows.begin(); i != _elbows.end(); i++)
		{
			CBoss2Elbow* elbow = (*i).second;
			elbow->Update(time);

			_is_change = elbow->_is_active;

			//Tất cả đồng loạt die khi máu cánh tay bằng 0
			if (_hp == 0)
			{
				elbow->_hp = 0;
			}
		}

		//Node chính sẽ lan truyền, kiểm tra để các node lân cận chuyển động theo
		_elbows[_id_main_node]->Spreading();

	}


	
}

void CBoss2Arm::Draw()
{
	if (_elbows.size() > 0)
	{
		for (map<int, CBoss2Elbow*>::iterator i = _elbows.begin(); i != _elbows.end(); i++)
		{
			CBoss2Elbow* elbow = (*i).second;
			elbow->Draw();
		}
	}
}