#ifndef _CGROUNDSTAR_H_
#define _CGROUNDSTAR_H_

#include "CGround.h"

class CGroundStar : public CGround
{
private:
	int _count;
	int _time_count;
	bool _isDraw;
	int _numSub; //so dc chia
	int _indexSprite;
public:
	CGroundStar(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CGroundStar();

	void LoadResources();
	void Draw();
	void Update(int delta_time);


};
#endif // !_CGROUNDSTAR_H_
