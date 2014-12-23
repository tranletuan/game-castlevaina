#include "CRunManManager.h"

CRunmanManager::CRunmanManager()
{
	LoadResources();
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

	vector<CObject*> list_notree = CResourcesManager::GetInstance()->listObNoTree;
	for (vector<CObject*>::iterator i = list_notree.begin(); i != list_notree.end(); i++)
	{
		CObject* ob = (*i);
		if (ob->_specific_type != RunMan) continue;

		D3DXVECTOR3 pos = D3DXVECTOR3(ob->_physical.x, ob->_physical.y, 0);
		_position_active.push_back(pos);
	}
}

void CRunmanManager::Update(int delta_time)
{
	CheckActive();

	if (_list_runman.size() > 0)
	{
		for (map<int, CRunman*>::iterator i = _list_runman.begin(); i != _list_runman.end(); i++)
		{
			int id = (*i).first;
			CRunman* runman = (*i).second;

			runman->Update(delta_time);

			if (!CheckRunManInView(runman->_physical.x, runman->_physical.y) || !runman->_enable)
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

void CRunmanManager::CheckActive()
{
	CCamera* cam = CResourcesManager::GetInstance()->_camera;

	for (int i = 0; i < _position_active.size(); i++)
	{
		D3DXVECTOR3 pos = _position_active.at(i);
		D3DXVECTOR3 pos_check_active = cam->Transform(pos);

		int curMap = CResourcesManager::GetInstance()->m_curMap;

		switch (curMap)
		{
		case 1:
		case 3:
			if ((pos_check_active.x < 0 && pos_check_active.x > -ENEMY_RUN_MAN_DISTANCE_ACTIVE) ||
				(pos_check_active.x < kScreenWidth + ENEMY_RUN_MAN_DISTANCE_ACTIVE && pos_check_active.x > kScreenWidth))
			{
				Attacking(pos);
			}
			break;
		case 2:
			break;
		}
	}
}

void CRunmanManager::Attacking(D3DXVECTOR3 pos)
{
	if(!_queue_runman.empty())
	{
		DWORD now = GetTickCount();
		if (now - _last_time >= ENEMY_RUN_MAN_ELAPSED_TIME_ATTACK)
		{
			CRunman* runman = _queue_runman.front();
			runman->SetTarget(pos, CResourcesManager::GetInstance()->m_posBill);

			_queue_runman.pop();
			_list_runman[runman->_id] = runman;
			_last_time = now;
		}
	}
}

void CRunmanManager::CheckCollisionWithGround(CObject* ground)
{
	if (_list_runman.size() > 0)
	{
		for (map<int, CRunman*>::iterator i = _list_runman.begin(); i != _list_runman.end(); i++)
		{
			CRunman* runman = (*i).second;

			//Kiểm tra va chạm với mặt đất
			CollisionDirection cd = runman->CheckCollision(ground);
			if (cd == TopCollision)
			{
				runman->Standing(ground->_physical.bounds.top + ENEMY_RUN_MAN_BOUNDS_HEIGHT / 2 + 0.5f, 
					ground->_specific_type);

				//Khi runman chạy hết đường thì hoặc là quay đầu, hoặc là nhảy
				if ((runman->_physical.bounds.left <= ground->_physical.bounds.left ||
					runman->_physical.bounds.right >= ground->_physical.bounds.right) &&
					runman->_rm_status == RMRun)
				{
					int ran = rand() % 10;
					if (ran < 7)
					{
						runman->Jumping();
					}
					else if (runman->_rm_status != RMJump)
					{
						runman->_physical.vx_last *= -1;
						runman->_physical.vx *= -1;

						if (runman->_physical.vx_last > 0)
						{
							runman->_physical.x += 10;
						}
						else
						{
							runman->_physical.x -= 10;
						}
					}
				}
			}
		}
	}
}

void CRunmanManager::CheckCollisionWithPlayer(CPlayerWeapon* weapon, CBill* player)
{
	if (_list_runman.size() > 0)
	{
		for (map<int, CRunman*>::iterator i = _list_runman.begin(); i != _list_runman.end(); i++)
		{
			CRunman* runman = (*i).second;

			//Kiểm tra va chạm với đạn người chơi 1
			if (runman->_hp > 0)
			{
				if (weapon->CheckCollision(runman) != NoCollision)
				{
					runman->_hp--;
					runman->Dying();
				}
			}

			//Kiểm tra va chạm với người chơi 1
			if (player->CheckCollision(runman) != NoCollision && player->_can_impact)
			{
				player->Dying();
			}
		}
	}
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

	if (x < c->view_port.x - ENEMY_RUN_MAN_DISTANCE_ACTIVE ||
		x > c->view_port.x + kScreenWidth + ENEMY_RUN_MAN_DISTANCE_ACTIVE) return false;

	if (y > c->view_port.y + ENEMY_RUN_MAN_DISTANCE_ACTIVE || 
		y < c->view_port.y - kScreenHeight - ENEMY_RUN_MAN_DISTANCE_ACTIVE) return false;

	return true;
}
