#ifndef QTNODE_H
#define QTNODE_H

#include <vector>
#include <string>
#include "CResourcesManager.h"

class CObject;
class QTNode
{
private:

	int m_levelMap;
	string m_id;
	int m_level;
	float m_posX;
	float m_posY;
	int m_width;
	int m_height;
	
	bool m_isLeaf; // la node la

	vector<CObject*> m_listOb;
	QTNode *m_nodelt; // left top
	QTNode *m_nodert; // right top
	QTNode *m_nodelb; // left bottom
	QTNode *m_noderb; // right bottom

public:

	QTNode();
	QTNode(string id, int level, float posX, float posY, int width, int height);
	~QTNode();

	void setNodeLT(QTNode *x){ m_nodelt = x; }
	void setNodeRT(QTNode *x){ m_nodert = x; }
	void setNodeLB(QTNode *x){ m_nodelb = x; }
	void setNodeRB(QTNode *x){ m_noderb = x; }
	QTNode* getNodeLT(){ return m_nodelt; }
	QTNode* getNodeRT(){ return m_nodert; }
	QTNode* getNodeLB(){ return m_nodelb; }
	QTNode* getNodeRB(){ return m_noderb; }

	void isLeaf(bool x){ m_isLeaf = x; }
	bool isLeaf(){ return m_isLeaf; }
	void setID(string x){ m_id = x; }
	string getID(){ return m_id; }
	void setLevel(int x){ m_level = x; }
	int getLevel(){ return m_level; }
	void setPosX(float x){ m_posX = x; }
	float getPosX(){ return m_posX; }
	void setPosY(float x){ m_posY = x; }
	float getPosY(){ return m_posY; }
	void setWidth(int x){ m_width = x; }
	int getWidth(){ return m_width; }
	void setHeight(int x){ m_height = x; }
	int getHeight(){ return m_height; }
	void setLevelMap(int x){ m_levelMap = x; }
	void setListOb(vector<CObject*> x){ m_listOb = x; }
	vector<CObject*> &getListOb(){ return m_listOb; }
	// chen danh sach cac doi tuong cua node la
	void setListOb(string x);
	
	


};

#endif