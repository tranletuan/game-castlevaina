﻿#include "CPlayerWeapon.h"

CPlayerWeapon::CPlayerWeapon()
{
	SetWaeponType(WPN);
	LoadResources();
}

CPlayerWeapon::~CPlayerWeapon()
{
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			CBullet* bullet = (*i).second;
			_queue_id_remove.push(bullet->_id);
		}

		RemoveDisabledBullet();
	}

	//NBullet
	while (!_queue_bullet_n.empty())
	{
		CBullet* bullet = _queue_bullet_n.front();
		_queue_bullet_n.pop();
		delete bullet;
	}

	//MBullet
	while (!_queue_bullet_m.empty())
	{
		CBullet* bullet = _queue_bullet_m.front();
		_queue_bullet_m.pop();
		delete bullet;
	}

	//SBullet
	while (!_queue_bullet_s.empty())
	{
		CBullet* bullet = _queue_bullet_s.front();
		_queue_bullet_s.pop();
		delete bullet;
	}

	//LBullet
	while (!_queue_bullet_l.empty())
	{
		CBullet* bullet = _queue_bullet_l.front();
		_queue_bullet_l.pop();
		delete bullet;
	}

	//FBullet
	while (!_queue_bullet_f.empty())
	{
		CBullet* bullet = _queue_bullet_f.front();
		_queue_bullet_f.pop();
		delete bullet;
	}

}

void CPlayerWeapon::SetWaeponType(PlayerWeaponType type)
{
	this->_player_waepon_type = type;
	if (type == WPN) _v_powerful = 0;
}

PlayerWeaponType CPlayerWeapon::GetWeaponType()
{
	return _player_waepon_type;
}

void CPlayerWeapon::SetVelocityPowerful(float vp)
{
	this->_v_powerful = vp;
}

bool CPlayerWeapon::Shooting(D3DXVECTOR3 pos, int angle, float vo)
{
	switch (_player_waepon_type)
	{
	case WPN:
		return ShootingNBullet(pos, angle, vo);
	case WPM:
		return ShootingMBullet(pos, angle, vo);
	case WPS:
		return ShootingSBullet(pos, angle, vo);
	case WPF:
		return ShootingFBullet(pos, angle, vo);
	case WPL:
		return ShootingLBullet(pos, angle, vo);
	}
}

CollisionDirection CPlayerWeapon::CheckCollision(CObject* obj)
{
	if (_list_bullet.size() > 0)
	{
		CollisionDirection collision = NoCollision;
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			CBullet* bullet = (*i).second;

			if (!bullet->_enable) continue;

			//Kiểm tra va chạm với 1 đối tượng
			collision = bullet->CheckCollision(obj);
			if (collision != NoCollision)
			{
				bullet->OnTarget();
				
				break;
			}
		}

		return collision;
	}

	return NoCollision;
}

void CPlayerWeapon::LoadResources()
{
	_audio_waepon = CResourcesManager::GetInstance()->m_audio;

	int id = 1;
	//NBullet
	for (int i = 0; i < BULLET_N_TOTAL; i++)
	{
		CBullet* bullet = new CNBullet(id++);
		bullet->LoadResources();
		_queue_bullet_n.push(bullet);
	}

	//MBullet
	for (int i = 0; i < BULLET_M_TOTAL; i++)
	{
		CBullet* bullet = new CMBullet(id++);
		bullet->LoadResources();
		_queue_bullet_m.push(bullet);
	}

	//FBullet
	for (int i = 0; i < BULLET_F_TOTAL; i++)
	{
		CBullet* bullet = new CFBullet(id++);
		bullet->LoadResources();
		_queue_bullet_f.push(bullet);
	}

	//LBullet
	for (int i = 0; i < BULLET_L_TOTAL; i++)
	{
		CBullet* bullet = new CLBullet(id++);
		bullet->LoadResources();
		_queue_bullet_l.push(bullet);
	}

	//SBullet
	for (int i = 0; i < BULLET_S_TOTAL; i++)
	{
		CBullet* bullet = new CSBullet(id++);
		bullet->LoadResources();
		_queue_bullet_s.push(bullet);
	}
}

//Support
bool CPlayerWeapon::ShootingNBullet(D3DXVECTOR3 pos, int angle, float vo)
{
	if (!_queue_bullet_n.empty())
	{
		CBullet* bullet = _queue_bullet_n.front();
		bullet->Shoot(pos, angle, BULLET_N_V + _v_powerful, vo);

		_queue_bullet_n.pop();
		_list_bullet[bullet->_id] = bullet;

		//play sound
		CResourcesManager::GetInstance()->sound_bullet_default->Reset();
		_audio_waepon->playSound(CResourcesManager::GetInstance()->sound_bullet_default);

		return true;
	}

	return false;
}

bool CPlayerWeapon::ShootingMBullet(D3DXVECTOR3 pos, int angle, float vo)
{
	if (!_queue_bullet_m.empty())
	{
		CBullet* bullet = _queue_bullet_m.front();
		bullet->Shoot(pos, angle, BULLET_M_V + _v_powerful, vo);

		_queue_bullet_m.pop();
		_list_bullet[bullet->_id] = bullet;

		//play sound		
		CResourcesManager::GetInstance()->sound_bullet_m->Reset();
		_audio_waepon->playSound(CResourcesManager::GetInstance()->sound_bullet_m);

		return true;
	}
	
	return false;
}

bool CPlayerWeapon::ShootingFBullet(D3DXVECTOR3 pos, int angle, float vo)
{
	if (!_queue_bullet_f.empty())
	{
		CBullet* bullet = _queue_bullet_f.front();
		bullet->Shoot(pos, angle, BULLET_F_V, 0);

		_queue_bullet_f.pop();
		_list_bullet[bullet->_id] = bullet;

		//play sound
		CResourcesManager::GetInstance()->sound_bullet_l->Reset();
		_audio_waepon->playSound(CResourcesManager::GetInstance()->sound_bullet_l);

		return true;
	}

	return false;
}

bool CPlayerWeapon::ShootingLBullet(D3DXVECTOR3 pos, int angle, float vo)
{
	//Xóa tất cả đạn trong list
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			CBullet* bullet = (*i).second;

			if (bullet->_specific_type == BulletL)
			{
				_queue_bullet_l.push(bullet);
			}
		}
	}

	//Tạo lại list đạn
	float _add_x = cos(D3DXToRadian(angle)) * BULLET_L_ELAPSED_DIS;
	float _add_y = sin(D3DXToRadian(angle)) * BULLET_L_ELAPSED_DIS;
	int _count = 0;
	while (!_queue_bullet_l.empty())
	{
		float x = pos.x + _add_x*_count;
		float y = pos.y + _add_y*_count;
		D3DXVECTOR3 position = D3DXVECTOR3(x, y, 0);

		CBullet* bullet = _queue_bullet_l.front();
		bullet->Shoot(position, angle, BULLET_L_V + _v_powerful, vo);

		_queue_bullet_l.pop();
		_list_bullet[bullet->_id] = bullet;
		_count++;
	}

	//play sound
	CResourcesManager::GetInstance()->sound_bullet_l->Reset();
	_audio_waepon->playSound(CResourcesManager::GetInstance()->sound_bullet_l);

	return true;
}

bool CPlayerWeapon::ShootingSBullet(D3DXVECTOR3 pos, int angle, float vo)
{
	int _count = 0;
	int _angle = angle;

	if (_queue_bullet_s.empty()) return false;

	while (!_queue_bullet_s.empty())
	{
		//1 phát bắn chỉ đạt được tốt đa 5 viên đạn
		if (_count == BULLET_S_COUNT_ONE_SHOOT) break;

		int _sign = _count % 2 == 0 ? 1 : -1;
		_angle = _count * BULLET_S_ELAPSED_DEGREES * _sign + _angle;

		CBullet* bullet = _queue_bullet_s.front();
		bullet->Shoot(pos, _angle, BULLET_S_V + _v_powerful, vo);

		_queue_bullet_s.pop();
		_list_bullet[bullet->_id] = bullet;
		_count++;
	}


	//play sound
	CResourcesManager::GetInstance()->sound_bullet_s->Reset();
	_audio_waepon->playSound(CResourcesManager::GetInstance()->sound_bullet_s);


	return true;
}

void CPlayerWeapon::RemoveDisabledBullet()
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
		case BulletN:
			_queue_bullet_n.push(bullet);
			break;
		case BulletM:
			_queue_bullet_m.push(bullet);
			break;
		case BulletS:
			_queue_bullet_s.push(bullet);
			break;
		case BulletF:
			_queue_bullet_f.push(bullet);
			break;
		case BulletL:
			_queue_bullet_l.push(bullet);
			break;
		}
	}
}
