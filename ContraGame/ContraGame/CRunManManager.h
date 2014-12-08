#ifndef _CRUN_MAN_MANAGER_H_
#define _CRUN_MAN_MANAGER_H_

#include "CResourcesManager.h"
#include "CRunman.h"
#include "CBill.h"
#include <map>
#include <queue>
#include <vector>

class CRunmanManager
{
protected:
	DWORD _last_time;

	map<int, CRunman*> _list_runman;
	queue<CRunman*> _queue_runman;
	queue<int> _queue_id_remove;
	vector<D3DXVECTOR3> _position_active;
	bool CheckRunManInView(float x, float y);
	void CheckActive();
	void Attacking(D3DXVECTOR3 pos);
public:
	CRunmanManager();
	~CRunmanManager();

	void RemoveDisableRunman();
	void CheckCollisionWithGround(CObject* ground);
	void CheckCollisionWithPlayer(CPlayerWeapon* weapon, CBill* player);

	void LoadResources();
	void Update(int delta_time);
	void Draw();
};
#endif // !_CRUN_MAN_MANAGER_H_
