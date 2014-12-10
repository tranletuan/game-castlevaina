#ifndef CGROUND_ELECTRON_H
#define CGROUND_ELECTRON_H

#include "CGround.h"

class CGroundElectron:
	public CGround
{
private:

public:
	CGroundElectron(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CGroundElectron();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

};


#endif