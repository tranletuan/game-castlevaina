#ifndef CSNIPERBLOCK_H
#define CSNIPERBLOCK_H

#include "CObject.h"

enum SniperBlockState
{
	SBS_Wait,
	SBS_Fire,
	SBS_Die,
};

class CSniperBlock
	:public CObject
{
private:
	int _timeDuring; // Thời gian chờ
	SniperBlockState _state;
	CSprite* _sprite_effect;
public:
	CSniperBlock(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CSniperBlock();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	void DrawWhenWait(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenFire(D3DXVECTOR3 pos);
};



#endif