#include "CListNoTree.h"

CListNoTree::CListNoTree()
{
	LoadResources();
}

CListNoTree::~CListNoTree()
{

}

void CListNoTree::LoadResources()
{
	_listObNoTree = CResourcesManager::GetInstance()->listObNoTree;

	vector<CObject*> listObNoneTreeX;
	for (int i = 0; i < _listObNoTree.size(); i++)
	{
		CObject *ob = getObjectTrust(_listObNoTree.at(i));
		listObNoneTreeX.push_back(ob);
	}
	_listObNoTree = listObNoneTreeX;
}

void CListNoTree::Draw()
{
	for (int i = 0; i < _listObNoTree.size(); i++)
	{
		if (_listObNoTree.at(i)->getEnable())
		{
			_listObNoTree.at(i)->Draw();
		}
	}
}

void CListNoTree::Update(int delta_time)
{
	for (int i = 0; i < _listObNoTree.size(); i++)
	{
		setActivity(_listObNoTree.at(i));

		if (_listObNoTree.at(i)->getEnable())
		{
			_listObNoTree.at(i)->Update(delta_time);
		}
	}
}

CObject *CListNoTree::getObjectTrust(CObject *x)
{
	float posX = x->getPosX() + x->getWidth() / 2;
	float posY = x->getPosY() - x->getHeight() / 2;
	CObject *ob = NULL;
	switch (x->getSpecificType())
	{
	case ItemM:
	case ItemF:
	case ItemB:
	case ItemL:
	case ItemR:
	case ItemS:
		ob = new CItemFly(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getTrack(), x->getWidth(), x->getHeight());
		break;
	case RunMan:
		ob = new CRunman(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());
		break;
	default:
		break;
	}
	return ob;

}

void CListNoTree::setActivity(CObject *x)
{
	CCamera *cam = CResourcesManager::GetInstance()->_camera;
	float posX = x->getPosX();
	float posY = x->getPosY();

	switch (x->getTrack())
	{
	case Track_LR:
		if (posX + x->getWidth() / 2 > CResourcesManager::GetInstance()->m_widthMap && x->getEnable())
		{
			x->setEnable(false);
		}
		if (posX + x->getWidth() / 2 < cam->getPosX())
		{
			x->setEnable(true);
		}
		break;
	case Track_RL:
		if (posX - x->getWidth() / 2 < cam->getPosX() && x->getEnable())
		{
			x->setEnable(false);
		}
		if (posX + x->getWidth() / 2 < cam->getPosX() + cam->getWidth())
		{
			x->setEnable(true);
		}
		break;
	case Track_UD:
		break;
	case Track_DU:
		if (x->getEnable() && posY - x->getHeight() / 2 >  CResourcesManager::GetInstance()->m_heightMap)
		{
			x->setEnable(false);
		}
		if (posY + x->getHeight() / 2 < cam->getPosY() - cam->getHeight())
		{
			x->setEnable(true);
		}
		break;
	default:
		break;
	}

}