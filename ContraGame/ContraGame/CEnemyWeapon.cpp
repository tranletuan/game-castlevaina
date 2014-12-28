﻿#include "CEnemyWeapon.h"

CEnemyWeapon::CEnemyWeapon()
{
	LoadResources();
}

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

	//B2Bullet
	for (int i = 0; i < BULLET_B2_TOTAL; i++)
	{
		CBullet* bullet = new CB2Bullet(id++);
		bullet->LoadResources();
		_queue_bullet_b2.push(bullet);
	}

	//MEBullet
	for (int i = 0; i < BULLET_ME_TOTAL; i++)
	{
		CBullet* bullet = new CMBullet(id++);
		bullet->LoadResources();
		_queue_bullet_me.push(bullet);
	}

	//SPBullet
	for (int i = 0; i < BULLET_SP_TOTAL; i++)
	{
		CBullet* bullet = new CSPBullet(id++);
		bullet->LoadResources();
		_queue_bullet_sp.push(bullet);
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
		case BulletB2:
			_queue_bullet_b2.push(bullet);
			break;
		case BulletM:
			_queue_bullet_me.push(bullet);
			break;
		case BulletSP:
			_queue_bullet_sp.push(bullet);
			break;
		}
	}
}

void CEnemyWeapon::CheckCollisionWithPlayer(CBill* player)
{
	for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
	{
		CBullet* bullet = (*i).second;

		if (bullet->CheckCollision(player) != NoCollision && player->_can_impact)
		{		
			player->Dying();
		}
	}
}

void CEnemyWeapon::CheckCollisionWithGround(CObject* ground)
{
	if (ground->_specific_type != Ground_Grass) return;
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			CBullet* bullet = (*i).second;
			if (bullet->_specific_type != BulletSP) continue;

			if (bullet->CheckCollision(ground) == TopCollision && 
				bullet->_physical.current_vy < 0)
			{
				bullet->OnTarget();
			}
		}
	}
}

void CEnemyWeapon::CheckCollisionWithWeaponPlayer(CPlayerWeapon* weapon)
{

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

int CEnemyWeapon::ShootingBulletB(D3DXVECTOR3 pos)
{
	if (!_queue_bullet_b.empty())
	{
		CBullet* bullet = _queue_bullet_b.front();
		bullet->Shoot(pos, 180, BULLET_B_VX, 0);

		_queue_bullet_b.pop();
		_list_bullet[bullet->_id] = bullet;
		return bullet->_id;
	}

	return -1;
}

int CEnemyWeapon::ShootingBulletB2(D3DXVECTOR3 pos, int angle, float vo)
{
	if (!_queue_bullet_b2.empty())
	{
		CBullet* bullet = _queue_bullet_b2.front();
		bullet->Shoot(pos, angle, BULLET_B2_V, vo);

		_queue_bullet_b2.pop();
		_list_bullet[bullet->_id] = bullet;
		return bullet->_id;
	}

	return -1;
}

int CEnemyWeapon::ShootingBulletME(D3DXVECTOR3 pos, int angle, float vo)
{
	if (!_queue_bullet_me.empty())
	{
		CBullet* bullet = _queue_bullet_me.front();
		bullet->Shoot(pos, angle, BULLET_ME_V, vo);

		_queue_bullet_me.pop();
		_list_bullet[bullet->_id] = bullet;
		return bullet->_id;
	}

	return -1;
}

int CEnemyWeapon::ShootingBulletSP(D3DXVECTOR3 pos, int angle, float vo)
{
	if (!_queue_bullet_sp.empty())
	{
		CBullet* bullet = _queue_bullet_sp.front();
		bullet->Shoot(pos, angle, BULLET_SP_VX, vo);

		_queue_bullet_sp.pop();
		_list_bullet[bullet->_id] = bullet;
		return bullet->_id;
	}

	return -1;
}