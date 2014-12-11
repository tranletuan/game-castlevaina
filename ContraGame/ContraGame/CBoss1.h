#ifndef CBOSS1_H
#define CBOSS1_H

#include "CObject.h"

enum Boss1State
{
	B1S_Acti, // dang hoat dong
	B1S_DieBadge,	
	B1S_DestroyBG1,
	B1S_DestroyBG2,
	B1S_DestroyBG3,
	B1S_DestroyBG4,
	B1S_NextMap,
};
class CBoss1
	: public CObject
{
private:
	CSprite* _sprite_bg; // background
	CSprite* _sprite_badge; // huy hieu
	CSprite* _sprite_effect; // sprite no
	CSprite* _sprite_effect1;
	CSprite* _sprite_effect2;
	CSprite* _sprite_effect3;
	CSprite* _sprite_effect4;
	Boss1State _state;
	bool _destroy_bg;
	int _time_counter;
	

public:
	CBoss1(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBoss1();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	// ve khi binh thuong
	void DrawWhenActi(D3DXVECTOR3 pos);
	// ve khi huy hiệu bị pá hủy
	void DrawWhenBadgeDie(D3DXVECTOR3 pos);
	// Ve khi destroy background
	void DrawWhenDestroyBG1(D3DXVECTOR3 pos);
	void DrawWhenDestroyBG2(D3DXVECTOR3 pos);
	void DrawWhenDestroyBG3(D3DXVECTOR3 pos);
	void DrawWhenDestroyBG4(D3DXVECTOR3 pos);
	// Ve khi next Map
	void DrawWhenNextMap(D3DXVECTOR3 pos);

	Boss1State getState() { return _state; }
	void setState(Boss1State x){ _state = x; }
};


#endif