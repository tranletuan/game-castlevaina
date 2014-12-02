#ifndef _CGROUNDEFFECT_H_
#define _CGROUNDEFFECT_H_

#include "CGround.h"

class CGroundEffect : public CGround
{
private:
	int _count;
	int _time_count;
	bool _isDraw;

public:
	CGroundEffect(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CGroundEffect();

	void LoadResources();
	void Draw();
	void Update(int delta_time);


};
#endif // !_CGROUND_H_
