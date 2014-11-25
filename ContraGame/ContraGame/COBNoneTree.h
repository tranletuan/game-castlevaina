#ifndef COBNONETREE_H
#define COBNONETREE_H

#include "CResourcesManager.h"
#include "CItemFly.h"

class COBNoneTree
{

private:
	vector<CObject*> _listObNoneTree;
public:
	COBNoneTree();
	~COBNoneTree();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	// get doi tuong chinh xac
	CObject* getObjectTrust(CObject *x);
	// kich hoat object hoat dong
	bool isActivity(CObject *x);

};


#endif