#include "CWaeponFactory.h"

CWaeponFactory::~CWaeponFactory()
{
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			CBullet* temp = (*i).second;
			delete temp;
		}

		_list_bullet.clear();
	}
}

bool CWaeponFactory::CheckBulletInView(float x, float y)
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;

	if (x < c->view_port.x || x > c->view_port.x + kScreenWidth) return false;
	if (y > c->view_port.y || y < c->view_port.y - kScreenHeight) return false;

	return true;
}
