#include "CEnemyUseGun.h"

CEnemyUseGun::CEnemyUseGun(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CEnemy(id, specific_type, pos, width, height)
{
}

CEnemyUseGun::~CEnemyUseGun()
{
}

void CEnemyUseGun::SetTarget(float x, float y)
{
	_target.x = x;
	_target.y = y;

	//vector chỉ phương của mục tiêu, xem như đối tượng enemy là tâm trục tọa độ
	D3DXVECTOR3 vector = D3DXVECTOR3(_target.x - _physical.x, _target.y - _physical.y, 0);

	//Trường hợp đặc biệt thứ 1
	if (vector.y == 0)
	{
		_target_angle = vector.x > 0 ? 0 : 180;
		return;
	}

	//Trường hợp đặc biệt thứ 2
	if (vector.x == 0)
	{
		_target_angle = vector.y > 0 ? 90 : 270;
	}

	_target_angle = D3DXToDegree(atan(vector.y / vector.x));
	_target_angle = vector.y > 0 ? _target_angle : _target_angle + 180;
}
