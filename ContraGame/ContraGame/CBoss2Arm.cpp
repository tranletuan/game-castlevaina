#include "CBoss2Arm.h"

CBoss2Arm::CBoss2Arm(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height, int direction)
	:CObject(id, specific_type, Enemy, pos, width, height)
{
	_hp = 20;
	_length = 5;
	_count_change = 0;
	_last_time_change = 0;
	_can_impact = false;
	_enable = false;
	_is_wait = true;
	_physical.vx_last = direction;
	LoadResources();
}

CBoss2Arm::~CBoss2Arm()
{
}

void CBoss2Arm::LoadResources()
{
	int id = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(_physical.x, _physical.y, 0);
	for (int i = 0; i < _length - 1; i++)
	{
		CBoss2Elbow* elbow = new CBoss2Elbow(id++, Boss2_Elbow, pos, 16, 16, _physical.vx_last);
		elbow->LoadResources();
		_elbows[elbow->_id] = elbow;

		if (elbow->_id > 0)
		{
			elbow->_pre = _elbows[elbow->_id - 1];
			_elbows[elbow->_id - 1]->_next = elbow;
		}
	}

	CBoss2Elbow* elbow = new CBoss2Hand(id++, Boss2_Hand, pos, 16, 16, _physical.vx_last);
	elbow->LoadResources();
	_elbows[elbow->_id] = elbow;

	if (elbow->_id > 0)
	{
		elbow->_pre = _elbows[elbow->_id - 1];
		_elbows[elbow->_id - 1]->_next = elbow;
	}

}

void CBoss2Arm::Update(int time)
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	CCamera* c = rs->_camera;
	if (c->view_port.y == rs->m_heightMap) _enable = true;

	if (!_enable) return;
	_can_impact = true;

	if (_is_wait)
	{
		if (_last_time_change == 0) _last_time_change = GetTickCount();
		DWORD now = GetTickCount();
		if (now - _last_time_change >= BOSS2_ARM_ELAPSED_CHANGE)
		{
			_last_time_change = 0;
			_is_wait = false;
		}
	}
	else
	{
		if (_hp > 0)
		{
			//Khởi động cánh tay trước khi quay
			if (!_is_boot)
			{
				for (int i = 0; i < _length; i++)
				{
					_is_boot = _elbows[i]->Boot(time);
				}
				return;
			}

			//Cập nhật tay quay
			DWORD  now = GetTickCount();
			if (now - _last_time_change >= BOSS2_ARM_ELAPSED_CHANGE)
			{
				_id_main_node = 1;
				_count_change++;

				//Tất cả các node nhỏ hơn node chính đều phải ngừng hoạt động
				for (int i = 0; i <= _id_main_node; i++)
				{
					_elbows[i]->SetDeactivate();
				}

				//Chu kỳ tay ngừng lại bắn 1 lần
				if (_count_change < 4)
				{
					_elbows[_id_main_node]->SetActive();
				}
				else
				{
					_count_change = 0;
				}

				_last_time_change = now;
			}

			//Node chính sẽ lan truyền, kiểm tra để các node lân cận chuyển động theo
			_elbows[_id_main_node]->Spreading(-1);
		}

		//Cập nhật từng node con
		for (int i = 0; i < _length; i++)
		{
			CBoss2Elbow* elbow = _elbows[i];

			//Chỉ cập nhật khi tất cả các node đã cập nhật xong
			if (_is_boot)
			{
				elbow->Update(time);
			}

			//Tất cả đồng loạt die khi máu cánh tay bằng 0
			if (_hp <= 0)
			{
				elbow->_hp = 0;
			}
		}
	}
}

void CBoss2Arm::Draw()
{
	if (_is_wait || !_enable) return;

	if (_elbows.size() > 0)
	{
		for (map<int, CBoss2Elbow*>::iterator i = _elbows.begin(); i != _elbows.end(); i++)
		{
			CBoss2Elbow* elbow = (*i).second;
			elbow->Draw();
			_enable = elbow->_enable;
		}
	}
}

vector<CPhysical> CBoss2Arm::GetListElement()
{
	vector<CPhysical> list_element;
	for (map<int, CBoss2Elbow*>::iterator i = _elbows.begin(); i != _elbows.end(); i++)
	{
		list_element.push_back((*i).second->_physical);
	}

	return list_element;
}