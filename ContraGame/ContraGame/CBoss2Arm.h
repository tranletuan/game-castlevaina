#ifndef _CBOSS2_ARM_H_
#define _CBOSS2_ARM_H_

#include "CBoss2Elbow.h"
#include "CBoss2Hand.h"

class CBoss2Arm : public CObject
{
protected:
	map<int, CBoss2Elbow*> _elbows;
	DWORD _last_time_change;
	DWORD _elapsed_time;
	int _id_main_node;
	int _length;
	bool _is_change;
	int _count_change;

public:
	CBoss2Arm(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBoss2Arm();

	void LoadResources();
	void Update(int time);
	void Draw();
	vector<CPhysical> GetListElement();
};
#endif // !_CBOSS2_ARM
