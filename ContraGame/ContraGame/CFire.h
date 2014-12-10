#ifndef _CFIRE_H
#define _CFIRE_H

#include "CObject.h"

class CFire :
	public CObject
{
private:
	int _posXEnd; // tọa độ kết thúc theo chiều X của khoảng hoạt động
	int _posXBegin; // tọa độ bắt đầu theo chiều X của khoảng hoạt động
	int _direction; // hướng di chuyển, =1 trai sang pai, =-1 pai qua trai

	bool _init; // cai dat toa do doi tuong
	CResourcesManager *rs;

public:
	CFire(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CFire();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	void DrawMove(D3DXVECTOR3 pos);

};
#endif // !_CFIRE_H