#ifndef CLISTITEMFLY_H
#define CLISTITEMFLY_H

#include "CObject.h"
#include "CItemFly.h"
#include "CRunman.h"
#include "CBill.h"

class CListItemFly
{

private:
	vector<CObject*> _listItems;

public:
	CListItemFly();
	~CListItemFly();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	void CheckCollisionWithPlayerAndWeapon(CPlayerWeapon* weapon, CBill* player);

	// get doi tuong chinh xac
	CObject* getObjectTrust(CObject *x);
	// kich hoat object hoat dong, Co draw hay update hay k
	void setActivity(CObject *x);
	//Lay list ob
	vector<CObject*> &getListOb(){ return _listItems; }
};

#endif