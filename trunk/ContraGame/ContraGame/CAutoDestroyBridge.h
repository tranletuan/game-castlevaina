#ifndef _CAUTO_DESTROY_BRIDGE_H_
#define _CAUTO_DESTROY_BRIDGE_H_

#include "CGround.h"
#include "CEffectObject.h"
#include <stdlib.h>

class CAutoDestroyBridge : public CGround
{
private:
	bool _is_destroy;
	CSprite* _effect_destroy_sprite;
	D3DXVECTOR3 _position_effect_destroy[GROUND_BRIDGE_DESTROY_EFFECT_COUNT];

public:
	CAutoDestroyBridge(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CAutoDestroyBridge();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	void SetTarget(float x); //Nhận vị trí của người chơi để tự động phá hủy

};
#endif // !_CAUTO_DESTROY_BRIDGE_H_
