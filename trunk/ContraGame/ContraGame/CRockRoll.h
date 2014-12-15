#ifndef _CROCKROLL_H
#define _CROCKROLL_H

#include "CObject.h"

enum RockState
{
	RS_Wait, // đợi bill vào khoảng target
	RS_Fall, // rơi có thể va chạm với mặt đất đầu tiên
	RS_Up, // nẩy lên
	RS_Die,// Bị nổ
	RS_OutView, // Ra khỏi view
};

class CRockRoll
	:public CObject
{
private:
	int _idGround; // ID viên gạch đã va chạm
	float _posYBegin; // Tọa độ điểm Y lúc ban đầu
	RockState _state; // trạng thái của viên đá
	CSprite *_sprite_effect; 
	int _timeDruing; // thời gian xuất hiện lại khi ra khỏi view

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
