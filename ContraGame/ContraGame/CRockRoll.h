#ifndef _CROCKROLL_H
#define _CROCKROLL_H

#include "CObject.h"

enum RockState
{
	RS_Wait, // đợi bill vào khoảng target
	RS_Fall, // rơi có thể va chạm với mặt đất đầu tiên
	RS_Through, // rơi k thể va chạm mặt đất đầu tiên
	RS_Die,// Bị nổ
};

class CRockRoll
	:public CObject
{
private:
	float _firstY; // Tọa độ va chạm đầu tiên
	bool  _isPass; // Có thể va chạm mà bỏ qua
	RockState _state; // trạng thái của viên đá
	CSprite *_sprite_effect; 

public:
	CRockRoll(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CRockRoll();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	void DrawWhenWait(D3DXVECTOR3 pos);
	void DrawWhenMove(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
};



#endif