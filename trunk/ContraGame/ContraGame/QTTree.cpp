#include "QTTree.h"

QTTree::QTTree()
{
	init();
}

QTTree::~QTTree()
{

}

void QTTree::init()
{
	m_levelMap = CResourcesManager::GetInstance()->m_levelMap;
	m_camera = CResourcesManager::GetInstance()->_camera;


	// load list
	vector<QTNode*> m_listNode;
	switch (m_levelMap)
	{
	case 1:
		m_listNode = CResourcesManager::GetInstance()->map1_listNode;
		break;
	case 2:
		break;
	default:
		break;
	}

	m_numSub = m_listNode.at(m_listNode.size() - 1)->getID().length() / 2; 
	map<int, CObject*> map_objects;
	// cap nhat lai list doi tuong trong node
	for (int i = 0; i < m_listNode.size();i ++)
	{
		if (m_listNode.at(i)->getLevel() == m_numSub)
		{			
			vector<CObject*> listOb;
			vector<CObject*> listObX = m_listNode.at(i)->getListOb();
			for (int j = 0; j < listObX.size(); j++)
			{	
				CObject* ob = listObX.at(j);

				if (map_objects[ob->_id] == NULL)
				{
					map_objects[ob->_id] = getObjectTrust(ob);
				}
				
				ob = map_objects[ob->_id];
				listOb.push_back(ob);
			}

			m_listNode.at(i)->setListOb(listOb);
		}
	}

	CResourcesManager::GetInstance()->map1_listNode = m_listNode;

	// cap nhat lai node da add cac node con	
	string Idi = "";
	string Idj = "";
	int leveli = 0;
	int levelj = 0;

	for (int i = 0; i < m_listNode.size(); i++)
	{
		leveli = m_listNode.at(i)->getLevel();
		for (int j = m_listNode.size() - 1; j >= 0; j--)
		{
			levelj = m_listNode.at(j)->getLevel();

			// set node leaf
			if (levelj == m_numSub)
			{
				m_listNode.at(j)->isLeaf(true);
			}
			// so sanh level node j voi node i
			if (leveli == (levelj - 1))
			{
				Idi = m_listNode.at(i)->getID();
				Idj = m_listNode.at(j)->getID();
				// so sanh id node j voi node i
				if (Idj.substr(0, Idj.length() - 2) == Idi)
				{
					// add vao cac node con
					{
						if (Idj.substr(Idj.length() - 2, Idj.length()) == "00")
						{
							// node left top
							m_listNode.at(i)->setNodeLT(m_listNode.at(j));
						}
						else if (Idj.substr(Idj.length() - 2, Idj.length()) == "10")
						{
							// node right top							
							m_listNode.at(i)->setNodeRT(m_listNode.at(j));
						}
						else if (Idj.substr(Idj.length() - 2, Idj.length()) == "01")
						{
							// node left bottom
							m_listNode.at(i)->setNodeLB(m_listNode.at(j));
						}
						else if (Idj.substr(Idj.length() - 2, Idj.length()) == "11")
						{
							// node right bottom
							m_listNode.at(i)->setNodeRB(m_listNode.at(j));
						}
					}
				}
			}
		}
	}

	// add list node vao node
	m_nodeRoot = new QTNode("", 0, 0.00, m_listNode.at(0)->getHeight() * 2, m_listNode.at(0)->getWidth() * 2, m_listNode.at(0)->getHeight() * 2);
	string iDr = "";
	for (int i = 0; i < 4; i++)
	{
		iDr = m_listNode.at(i)->getID();
		if (iDr.substr(iDr.length() - 2, iDr.length()) == "00")
		{
			// node left top
			m_nodeRoot->setNodeLT(m_listNode.at(i));
		}
		else if (iDr.substr(iDr.length() - 2, iDr.length()) == "10")
		{
			// node right top							
			m_nodeRoot->setNodeRT(m_listNode.at(i));
		}
		else if (iDr.substr(iDr.length() - 2, iDr.length()) == "01")
		{
			// node left bottom
			m_nodeRoot->setNodeLB(m_listNode.at(i));
		}
		else if (iDr.substr(iDr.length() - 2, iDr.length()) == "11")
		{
			// node right bottom
			m_nodeRoot->setNodeRB(m_listNode.at(i));
		}
	}

}

void QTTree::getObjectInView()
{
	// lay node la va cham voi camera
	vector<QTNode *> node;
	vector<QTNode *> tam;
	int size = 1;
	node.push_back(m_nodeRoot);
	for (int i = 0; i < m_numSub; i++)
	{
		size = node.size();
		for (int j = 0; j < size; j++)
		{
			tam = getNodeCollWithCam(node.at(j));
			for (int k = 0; k < tam.size(); k++)
			{
				node.push_back(tam.at(k));
			}
		}
		node.erase(node.begin(), node.begin() + size);

	}

	// lay cac node nam trong node giao voi camera
	m_listObInView.clear();
	map<int, bool> check_id;
	for (int i = 0; i < node.size(); i++)
	{
		vector<CObject*> ob_in_node = node.at(i)->getListOb();
	
		for (vector<CObject*>::iterator j = ob_in_node.begin(); j != ob_in_node.end(); j++)
		{
			CObject* ob = (*j);
			if (!check_id[ob->_id])
			{
				m_listObInView.push_back(ob);
				check_id[ob->_id] = true;
			}
		}
	}

	CResourcesManager::GetInstance()->listObinView = m_listObInView;
	
}

void QTTree::update(int time)
{
	getObjectInView();


	for (int i = 0; i < m_listObInView.size(); i++)
	{		
		m_listObInView.at(i)->Update(time);		
	}
}

void QTTree::draw()
{
	for (int i = 0; i < m_listObInView.size(); i++)
	{
		m_listObInView.at(i)->Draw();		
	}
}

bool QTTree::isCollWithCam(QTNode *node)
{
	return !(node->getPosX() + node->getWidth() < m_camera->getPosX() || node->getPosX() > m_camera->getPosX() + m_camera->getWidth()
		|| node->getPosY() - node->getHeight() > m_camera->getPosY() || node->getPosY() < m_camera->getPosY() - m_camera->getHeight());

}


CObject * QTTree::getObjectTrust(CObject *x)
{
	// chuyển tọa độ từ top - left sang center
	float posX = x->getPosX() + x->getWidth() / 2;
	float posY = x->getPosY() - x->getHeight() / 2;

	switch (x->getSpecificType())
	{
	case Ground_Grass:
	case Ground_Water:
		return new CGround(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());
	case Sniper_Stand:
		return new CSniperStand(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());
	case ItemM_Stand:
	case ItemF_Stand:
	case ItemS_Stand:
		return new CItemStand(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());
	case Ground_Effect1:
		return new CGroundEffect(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());
	case Wall_Turret:
		return new CWallTurret(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());
	case Ground_Canon:
		return new CGroundCanon(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());
	case Boss1:
		return new CBoss1(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());		
	case Sniper_Hide:
		return new CSniperHide(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());		
	case Ground_Bridge:
		return new CAutoDestroyBridge(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getWidth(), x->getHeight());
	default:
		break;
	}
}

vector<QTNode*> QTTree::getNodeCollWithCam(QTNode *node)
{
	vector<QTNode*> x;
	if (isCollWithCam(node->getNodeLB()))
	{
		x.push_back(node->getNodeLB());
	}
	if (isCollWithCam((node->getNodeLT())))
	{
		x.push_back(node->getNodeLT());
	}
	if (isCollWithCam((node->getNodeRT())))
	{
		x.push_back(node->getNodeRT());
	}
	if (isCollWithCam((node->getNodeRB())))
	{
		x.push_back(node->getNodeRB());
	}
	return x;
}