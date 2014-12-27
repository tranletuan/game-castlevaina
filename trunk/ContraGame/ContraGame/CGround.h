#ifndef _CGROUND_H_
#define _CGROUND_H_

#include "CObject.h"

class CGround : public CObject
{
private:	
	
public:
	int _count;
	CGround(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CGround();

	virtual void LoadResources();
	virtual void Draw();
	virtual void Update(int delta_time);


};
#endif // !_CGROUND_H_
