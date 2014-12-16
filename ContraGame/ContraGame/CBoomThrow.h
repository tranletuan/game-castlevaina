#ifndef CBOOMTHROW_H
#define CBOOMTHROW_H

#include "CObject.h"

enum BoomState
{
	BoS_Wait, // Đợi hồi sinh
	BoS_Die, // Nổ
	BoS_Throw,// Ném
};
class CBoomThrow
	:public CObject
{
private:
	CSprite* _sprite_effect;
	int _timeDuring; // thời gian hồi sinh lại
	BoomState _state;
	D3DXVECTOR3 _posBegin; // tọa độ ban đầu

public:
	CBoomThrow(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBoomThrow();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenThrow(D3DXVECTOR3 pos);

};



#endif