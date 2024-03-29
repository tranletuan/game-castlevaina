#ifndef _CEFFECT_OBJECT_H_
#define _CEFFECT_OBJECT_H_
#include "CObject.h"

class CEffectObject : public CObject
{
protected:
	int _effect_time;
public:
	CEffectObject(SpecificType specific_type, D3DXVECTOR3 pos, int effect_time);
	CEffectObject(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CEffectObject();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
};
#endif // !_CEFFECT_OBJECT_H_
