#include "CRunManManager.h"

CRunmanManager::CRunmanManager()
{
}

CRunmanManager::~CRunmanManager()
{
}

void CRunmanManager::LoadResources()
{
	int id = 0;
	for (int i = 0; i < ENEMY_RUN_MAN_TOTAL; i++)
	{
		CRunman* runman = new CRunman(
			id++, 
			RunMan, 
			D3DXVECTOR3(0, 0, 0), 
			ENEMY_RUN_MAN_BOUNDS_WIDTH, 
			ENEMY_RUN_MAN_BOUNDS_HEIGHT);

		runman->LoadResources();
		_queue_runman.push(runman);
	}
}

void CRunmanManager::Update(int delta_time)
{
	if (_list_runman.size() > 0)
	{
		for (map<int, CRunman*>::iterator i = _list_runman.begin(); i != _list_runman.end(); i++)
		{
			int id = (*i).first;
			CRunman* runman = (*i).second;

			runman->Update(delta_time);

			if (!CheckRunManInView(runman->_physical.x, runman->_physical.y))
			{
				_queue_id_remove.push(runman->_id);
			}
		}

		RemoveDisableRunman();
	}
}

void CRunmanManager::Draw()
{
	if (_list_runman.size() > 0)
	{
		for (map<int, CRunman*>::iterator i = _list_runman.begin(); i != _list_runman.end(); i++)
		{
			int id = (*i).first;
			CRunman* runman = (*i).second;

			runman->Draw();
		}
	}
}

CollisionDirection CRunmanManager::CheckCollision(vector<CObject*>* list_ground, CObject* player)
{
	return LeftCollision;
}

void CRunmanManager::RemoveDisableRunman()
{
	while (!_queue_id_remove.empty())
	{
		int id = _queue_id_remove.front();

		CRunman* runman = _list_runman.at(id);
		_list_runman.erase(id); //Xóa khỏi list đạn có hiệu lực
		_queue_id_remove.pop();

		//Viên đạn nào đã vô hiệu quá đưa về hàng đợi của loại đạn đó
		switch (runman->_specific_type)
		{
		case RunMan:
			_queue_runman.push(runman);
			break;
		}
	}
}

bool CRunmanManager::CheckRunManInView(float x, float y)
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;

	if (x < c->view_port.x || x > c->view_port.x + kScreenWidth) return false;
	if (y > c->view_port.y || y < c->view_port.y - kScreenHeight) return false;

	return true;
}
