#include "CBoss2Hand.h"

CBoss2Hand::CBoss2Hand(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height, int direction)
	:CBoss2Elbow(id, specific_type, pos, width, height, direction)
{
	_hp = 1;
	_max_bullet = BOSS2_ARM_MAX_BULLET;
	LoadResources();
}

CBoss2Hand::~CBoss2Hand()
{
}

void CBoss2Hand::Update(int time)
{
	CBoss2Elbow::Update(time);

	D3DXVECTOR2 pos_target = CResourcesManager::GetInstance()->m_posBill;
	SetTarget(pos_target.x, pos_target.y);

	//Cập nhật lại những viên đạn có thể bắn trong list của enemy
	_weapon->UpdateQueueIdBullet(_queue_id_bullet);
}

bool CBoss2Hand::CheckTarget()
{
	if (abs(_physical.x - _target.x) <= ENEMY_ATTACK_DISTANCE)
	{
		return true;
	}

	return false;
}

void CBoss2Hand::SetTarget(float x, float y)
{
	CEnemyWeapon* wp = CResourcesManager::GetInstance()->_weapon_enemy;
	SetWeapon(wp);

	_target.x = x;
	_target.y = y;

	if (!CheckTarget()) return; //Mục tiêu chưa vào khoảng cách tấn công

	//vector chỉ phương của mục tiêu, xem như đối tượng enemy là tâm trục tọa độ
	D3DXVECTOR3 vector = D3DXVECTOR3(_target.x - _x_circle, _target.y - _y_circle, 0);

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

	if (_weapon != NULL && !_is_active)
	{
		Attacking();
	}
}

void CBoss2Hand::Attacking()
{
	if (_hp == 0) return;
	if (!CheckTarget()) return; //Mục tiêu chưa vào tầm tấn công

	//Kiểm tra số đạn đã bắn, nếu vẫn còn bắn được thì bắn
	if (_queue_id_bullet.size() < _max_bullet)
	{
		//Lấy góc bắn
		//2 góc liền kề với góc của mục tiêu
		int angle_1 = _target_angle / ENEMY_ATTACK_DEGREES * ENEMY_ATTACK_DEGREES;
		int angle_2 = angle_1 + ENEMY_ATTACK_DEGREES;

		_attack_angle = (angle_2 - _target_angle) < (_target_angle - angle_1) ? angle_2 : angle_1;
		_attack_angle %= 360;

		//Bắn
		int id = _weapon->ShootingBulletB2(D3DXVECTOR3(_x_circle, _y_circle, 0), _attack_angle, 0);

		if (id >= 0)
		{
			_queue_id_bullet.push(id);
		}
	}
}