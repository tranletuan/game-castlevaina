#ifndef CITEMSTAND_H
#define CITEMSTAND_H

#include "CObject.h"

enum SItemStand
{
	SIS_Close, // Sate Item Stand đóng
	SIS_Open, // chưa có thể bắn
	SIS_Enable, // có thể bắn
	SIS_Spatter // Bị pá hiểu và văng
};

class CItemStand :
	public CObject
{
private:
	CSprite *_sprite_effect;
	CSprite *_sprite_item;
	CSprite *_sprite_stand;	

	D3DXVECTOR3 _pos_stand; // tọa độ đứng yên
	SItemStand _state_item_stand;

public:
	CItemStand(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CItemStand();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	// ve cua item stand, khi chua vung hoat dong, dong' lai
	void DrawWhenStand(D3DXVECTOR3 pos);
	// ve cua item stand, khi da hoat dong dong mo item
	void DrawWhenActivity(D3DXVECTOR3 pos);
	// khi bi bat vo
	void DrawWhenAttack(D3DXVECTOR3 pos);

	
	int getHp(){ return _hp; }
	void setHp(int x){ _hp = x; }
	void setSIS(SItemStand x){ _state_item_stand = x; }
	SItemStand getSIS(){ return _state_item_stand; }
};

#endif