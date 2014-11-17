#include "CWaepon.h"

CWaepon::~CWaepon()
{
	if (_list_bullet.size() > 0)
	{
		_list_bullet.clear();
	}
}

bool CWaepon::CheckBulletInView(float x, float y)
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;

	if (x < c->view_port.x || x > c->view_port.x + kScreenWidth) return false;
	if (y > c->view_port.y || y < c->view_port.y - kScreenHeight) return false;

	return true;
}

void CWaepon::Update(int delta_time)
{
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			int id = (*i).first;
			CBullet* bullet = (*i).second;

			//Bỏ qua những viên đạn vô hiệu
			if (!bullet->_enable) continue;

			//Cập nhật vật lý của đạn
			bullet->Update(delta_time);

			//Kiểm tra đạn có nằm trong màn hình không
			if (!CheckBulletInView(bullet->_physical.x, bullet->_physical.y))
			{
				bullet->OnTarget();
				_queue_id_remove.push(bullet->_id);
			}
		}

		//Xóa những viên đạn không còn hiệu lực
		RemoveDisabledBullet();
	}
}

void CWaepon::Draw()
{
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			(*i).second->Draw();
		}
	}
}
