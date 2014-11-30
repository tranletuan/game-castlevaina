#ifndef CLISTNOTREE_H
#define CLISTNOTREE_H

#include "CObject.h"
#include "CItemFly.h"

class CListNoTree
{

private:
	vector<CObject*> _listObNoTree;

public:
	CListNoTree();
	~CListNoTree();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	// get doi tuong chinh xac
	CObject* getObjectTrust(CObject *x);
	// kich hoat object hoat dong, Co draw hay update hay k
	void setActivity(CObject *x);
	//Lay list ob
	vector<CObject*> &getListOb(){ return _listObNoTree; }
};

#endif