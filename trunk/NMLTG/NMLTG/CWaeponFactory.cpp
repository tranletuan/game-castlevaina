#include "CWaeponFactory.h"

CWaeponFactory::~CWaeponFactory()
{
	if (_list_bullet.size() > 0)
	{
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
