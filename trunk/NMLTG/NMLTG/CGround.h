#ifndef _CGROUND_H_
#define _CGROUND_H_

#include "CObject.h"

class CGround : public CObject
{
public:
	CGround(SpecificType specific_type, D3DXVECTOR3 pos);
	~CGround();

	virtual void LoadResources();
	virtual void Draw();
};
#endif // !_CGROUND_H_
