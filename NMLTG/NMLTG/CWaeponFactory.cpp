#include "CWaeponFactory.h"

CWaeponFactory::~CWaeponFactory()
{
	if (_list_bullet.size() > 0)
	{
		for (map<string, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			CBullet* temp = (*i).second;
			delete temp;
		}

		_list_bullet.clear();
	}
}