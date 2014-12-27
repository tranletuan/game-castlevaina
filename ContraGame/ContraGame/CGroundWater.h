#ifndef CGROUND_WATER_H
#define CGROUND_WATER_H

#include "CGround.h"

class CGroundWater:
	public CGround
{
private:

public:
	CGroundWater(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CGroundWater();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

};


#endif