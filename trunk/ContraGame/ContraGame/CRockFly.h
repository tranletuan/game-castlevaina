#ifndef _CROCKFLY_H_
#define _CROCKFLY_H_

#include "CGround.h"

class CRockFly : 
	public CGround
{
private:
	int _posXEnd; // tọa độ kết thúc theo chiều X của khoảng hoạt động
	int _posXBegin; // tọa độ bắt đầu theo chiều X của khoảng hoạt động
	int _direction; // hướng di chuyển

public:
	CRockFly(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CRockFly();

	void LoadResources();
	void Draw();	
	void Update(int delta_time);

	void DrawMove(D3DXVECTOR3 pos);
};
#endif // _CROCKFLY_H_

