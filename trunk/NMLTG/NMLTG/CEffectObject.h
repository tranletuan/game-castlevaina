#ifndef _CEFFECT_OBJECT_H_
#define _CEFFECT_OBJECT_H_
#include "CObject.h"

class CEffectObject : public CObject
{
protected:
	int _effect_time;
public:
	CEffectObject(SpecificType specific_type, D3DXVECTOR3 pos, int effect_time);
	~CEffectObject();

	void LoadResources();
	void Draw();
};
#endif // !_CEFFECT_OBJECT_H_
