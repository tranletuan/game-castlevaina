#include "QTNode.h"

QTNode::QTNode()
{
	m_id = "";
	m_level = 0;
	m_posX = 0;
	m_posY = 0;
	m_width = 0;
	m_height = 0;

	m_nodelb = NULL;
	m_nodelt = NULL;
	m_noderb = NULL;
	m_nodert = NULL;

	m_isLeaf = false;
	m_levelMap = 0;
}

QTNode::QTNode(string id, int level, float posX, float posY, int width, int height)
{
	m_id = id;
	m_level = level;
	m_posX = posX;
	m_posY = posY;
	m_width = width;
	m_height = height;

	m_nodelb = NULL;
	m_nodelt = NULL;
	m_noderb = NULL;
	m_nodert = NULL;

	m_isLeaf = false;
	m_levelMap = 0;
}

QTNode::~QTNode()
{

}


void QTNode::setListOb(string str)
{
	vector<CObject*> listObLoad = CResourcesManager::GetInstance()->map_listOb;	

	string delimiter = ",";	
	size_t pos = 0;
	std::string token;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		int id = atoi(token.c_str());
		for (int i = 0; i < listObLoad.size(); i++)
		{
			if (listObLoad.at(i)->getID() == id)
			{
				m_listOb.push_back(listObLoad.at(i));
			}
		}
		str.erase(0, pos + delimiter.length());
	}

}