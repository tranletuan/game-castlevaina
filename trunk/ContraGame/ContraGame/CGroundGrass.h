#ifndef CGROUND_GRASS_H
#define CGROUND_GRASS_H

#include "CGround.h"

class CGroundGrass:
	public CGround
{
private:

public:
	CGroundGrass(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CGroundGrass();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

};


#endif