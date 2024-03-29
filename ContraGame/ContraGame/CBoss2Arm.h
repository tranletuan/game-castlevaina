#ifndef _CBOSS2_ARM_H_
#define _CBOSS2_ARM_H_

#include "CBoss2Elbow.h"
#include "CBoss2Hand.h"

class CBoss2Arm : public CObject
{
protected:
	map<int, CBoss2Elbow*>	_elbows;
	DWORD					_last_time_change;
	int						_id_main_node;
	int						_length;
	int						_count_change;
	bool					_is_boot;
	bool					_is_change;
	bool					_is_wait;

public:
	CBoss2Arm(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height, int direction);
	~CBoss2Arm();

	void LoadResources();
	void Update(int time);
	void Draw();
	vector<CPhysical> GetListElement();
};
#endif // !_CBOSS2_ARM
