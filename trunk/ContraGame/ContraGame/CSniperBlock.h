#ifndef CSNIPERBLOCK_H
#define CSNIPERBLOCK_H

#include "CObject.h"

class CSniperBlock
	:public CObject
{
private:

public:
	CSniperBlock(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CSniperBlock();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

};



#endif