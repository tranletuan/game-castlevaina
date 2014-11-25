#ifndef CITEMFLY_H
#define CITEMFLY_H

#include "CObject.h"

enum SItemFly
{
	SIF_Move, // State item fly di chuyen
	SIF_Die, // Bị bắn	
};

class CItemFly
	:CObject
{
private:
	CSprite *_sprite_effect;
	CSprite *_sprite_item;

	SItemFly _state_item_fly;
	D3DXVECTOR3 _pos_effect;
	float _posY_center; // tọa độ tâm dao động của đồ thị cos
	int _time_counter;
	int _counter; // Biến đếm để giảm số lần vẽ item
public:
	int _hp;
	CItemFly(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);	
	~CItemFly();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	// Di chuyển theo đồ thị hình cos
	void MoveFollowCos(int delta_time);
	// Di chuyển khi die
	void MoveWhenDie(int delta_time);
	// Vẽ khi di chuyển
	void DrawWhenMove(D3DXVECTOR3 pos);
	// Vẽ khi bị bắt
	void DrawWhenDie(D3DXVECTOR3 pos);

	SItemFly getSIF(){ return _state_item_fly; }
	void setSIF(SItemFly x){ _state_item_fly = x; }
};


#endif
