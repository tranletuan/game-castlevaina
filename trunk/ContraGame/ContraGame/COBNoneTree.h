#ifndef COBNONETREE_H
#define COBNONETREE_H

#include "CObject.h"

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

};


#endif