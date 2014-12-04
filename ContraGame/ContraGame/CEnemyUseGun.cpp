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
	CEnemyWeapon* wp = CResourcesManager::GetInstance()->_weapon_enemy;
	SetWeapon(wp);

	_target.x = x;
	_target.y = y;

	if (!CheckTarget()) return; //Mục tiêu chưa vào khoảng cách tấn công

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

	if (vector.x < 0)
	{
		_target_angle += 180;
	}
	else if (vector.x > 0 && vector.y < 0)
	{
		_target_angle += 360;
	}
}
