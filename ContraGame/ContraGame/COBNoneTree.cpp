#include "COBNoneTree.h"

COBNoneTree::COBNoneTree()
{
	LoadResources();
}

COBNoneTree::~COBNoneTree()
{
	
}

void COBNoneTree::LoadResources()
{
	_listObNoneTree = CResourcesManager::GetInstance()->listObNoneTree;

	vector<CObject*> listObNoneTreeX;
	for (int i = 0; i < _listObNoneTree.size(); i++)
	{
		CObject *ob = getObjectTrust(_listObNoneTree.at(i));
		listObNoneTreeX.push_back(ob);
	}
	_listObNoneTree = listObNoneTreeX;
}

void COBNoneTree::Draw()
{
	for (int i = 0; i < _listObNoneTree.size(); i++)
	{
		if (isActivity(_listObNoneTree.at(i)))
		{
			_listObNoneTree.at(i)->Draw();
		}
	}
}

void COBNoneTree::Update(int delta_time)
{
	for (int i = 0; i < _listObNoneTree.size(); i++)
	{
		if (isActivity(_listObNoneTree.at(i)))
		{
			_listObNoneTree.at(i)->Update(delta_time);
		}
		
	}
}

CObject *COBNoneTree::getObjectTrust(CObject *x)
{	
	float posX = x->getPosX() + x->getWidth() / 2;
	float posY = x->getPosY() - x->getHeight() / 2;
	CObject *ob = new CItemFly(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());
	ob->_physical.vx_last = x->_physical.vx_last;
	return ob;
}

bool COBNoneTree::isActivity(CObject *x)
{	
	CCamera *cam = CResourcesManager::GetInstance()->_camera;
	int levelMap = CResourcesManager::GetInstance()->m_levelMap;

	float posX = x->getPosX() ;
	float posY = x->getPosY();
	float direc = x->_physical.vx_last;

	switch (levelMap)
	{
	case 1:
	case 3:
		// huong tu trai sang phai
		if (direc == 0)
		{  
			if (posX + x->getWidth() / 2 <= cam->getPosX())
			{	
				x->_physical.vx_last = 5;
				return true;
			}			
		}
		else if (direc == 1)
		{
			if (posX - x->getWidth() / 2 <= cam->getPosX() + cam->getWidth())
			{
				x->_physical.vx_last = 5;
				return true;
			}
		}
		else if (direc == 5)
		{
			return true;
		}
		break;
	case 2:
		break;
	default:
		break;
	}

	return false;
}