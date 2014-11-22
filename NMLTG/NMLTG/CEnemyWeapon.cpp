#include "CEnemyWeapon.h"

CEnemyWeapon::CEnemyWeapon()
{}

CEnemyWeapon::~CEnemyWeapon()
{
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			CBullet* bullet = (*i).second;
			bullet->OnTarget();
		}

		RemoveDisabledBullet();
	}

	//delete NEBullet
	while (!_queue_bullet_ne.empty())
	{
		CBullet* bullet = _queue_bullet_ne.front();
		_queue_bullet_ne.pop();
		delete bullet;
	}

	//delete BBullet
	while (!_queue_bullet_b.empty())
	{
		CBullet* bullet = _queue_bullet_b.front();
		_queue_bullet_b.pop();
		delete bullet;
	}
}

void CEnemyWeapon::LoadResources()
{
	int id = 1;

	//NEBullet
	for (int i = 0; i < BULLET_NE_TOTAL; i++)
	{
		CBullet* bullet = new CNEBullet(id++);
		bullet->LoadResources();
		_queue_bullet_ne.push(bullet);
	}

	//BBullet
	for (int i = 0; i < BULLET_B_TOTAL; i++)
	{
		CBullet* bullet = new CBBullet(id++);
		bullet->LoadResources();
		_queue_bullet_b.push(bullet);
	}
}

void CEnemyWeapon::RemoveDisabledBullet()
{
	while (!_queue_id_remove.empty())
	{
		int id = _queue_id_remove.front();

		CBullet* bullet = _list_bullet.at(id);
		_list_bullet.erase(id); //Xóa khỏi list đạn có hiệu lực
		_queue_id_remove.pop();

		//Viên đạn nào đã vô hiệu quá đưa về hàng đợi của loại đạn đó
		switch (bullet->_specific_type)
		{
		case BulletNE:
			_queue_bullet_ne.push(bullet);
			break;
		case BulletB:
			_queue_bullet_b.push(bullet);
			break;
		}
	}
}

CollisionDirection CEnemyWeapon::CheckCollision(CObject* obj)
{
	return TopCollision;
}

void CEnemyWeapon::UpdateQueueIdBullet(queue<int> &queue_id_bullet)
{
	int i = 0;
	int max = queue_id_bullet.size();

	while (!queue_id_bullet.empty() && i < max)
	{
		int id = queue_id_bullet.front();
		queue_id_bullet.pop();

		if (_list_bullet.find(id) != _list_bullet.end())
		{
			queue_id_bullet.push(id);
		}
		
		i++;
	}
}

int CEnemyWeapon::ShootingBulletNE(D3DXVECTOR3 pos, int angle, float vo)
{
	if (!_queue_bullet_ne.empty())
	{
		CBullet* bullet = _queue_bullet_ne.front();
		bullet->Shoot(pos, angle, BULLET_NE_V, vo);

		_queue_bullet_ne.pop();
		_list_bullet[bullet->_id] = bullet;
		return bullet->_id;
	}

	return -1;
}

int CEnemyWeapon::ShootingBulletB(D3DXVECTOR3 pos, int angle, float vo)
{
	if (!_queue_bullet_b.empty())
	{
		CBullet* bullet = _queue_bullet_b.front();
		bullet->Shoot(pos, angle, BULLET_B_VX, vo);

		_queue_bullet_b.pop();
		_list_bullet[bullet->_id] = bullet;
		return bullet->_id;
	}

	return -1;
}