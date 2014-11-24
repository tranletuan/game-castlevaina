#ifndef CITEM_H
#define CITEM_H

#include "CObject.h"

class CItemStand :
	CObject
{
private:
	CSprite *_sprite_effect;
	CSprite *_sprite_item;
	CSprite *_sprite_stand;	

	D3DXVECTOR3 _pos_stand; // tọa độ đứng yên

public:
	int _hp;
	CItemStand(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CItemStand();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	// ve cua item stand, khi chua vung hoat dong, dong' lai
	void DrawWhenStand();
	// ve cua item stand, khi da hoat dong dong mo item
	void DrawWhenActivity();
	// khi bi bat vo
	void DrawWhenAttack(D3DXVECTOR3 pos);

	
	int getHp(){ return _hp; }
	void setHp(int x){ _hp = x; }
};

#endif