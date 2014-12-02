#ifndef _CRUN_MAN_MANAGER_H_
#define _CRUN_MAN_MANAGER_H_

#include "CResourcesManager.h"
#include "CRunman.h"
#include <map>
#include <queue>
#include <vector>

class CRunmanManager
{
protected:
	map<int, CRunman*> _list_runman;
	queue<CRunman*> _queue_runman;
	queue<int> _queue_id_remove;
	bool CheckRunManInView(float x, float y);
public:
	CRunmanManager();
	~CRunmanManager();

	void RemoveDisableRunman();
	CollisionDirection CheckCollision(vector<CObject*>* list_ground, CObject* player);

	void LoadResources();
	void Update(int delta_time);
	void Draw();
};
#endif // !_CRUN_MAN_MANAGER_H_
