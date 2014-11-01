#include "CPlayerWaepon.h"

CPlayerWaepon::CPlayerWaepon()
{
	SetWaeponType(NBullet);
	_v_powerful = 0;
	for (int i = 0; i < BULLET_S_COUNT; i++)
	{
		_id_bullet[i] = 0;
	}
}

CPlayerWaepon::~CPlayerWaepon()
{
	CWaeponFactory::~CWaeponFactory();
}

void CPlayerWaepon::SetWaeponType(PlayerWaeponType type)
{
	this->_player_waepon_type = type;
	if (type == NBullet)
		_v_powerful = 0;
	if (type != SBullet) 
		_max_count = BULLET_N_COUNT;
	else 
		_max_count = BULLET_S_COUNT;
}

void CPlayerWaepon::SetVelocityPowerful(float vp)
{
	this->_v_powerful = vp;
}

void CPlayerWaepon::Shooting(D3DXVECTOR3 pos, int angle, float vo)
{
	switch (_player_waepon_type)
	{
	case NBullet:
		ShootingNBullet(pos, angle, vo);
		break;
	case MBullet:
		ShootingMBullet(pos, angle, vo);
		break;
	case SBullet:
		ShootingSBullet(pos, angle, vo);
		break;
	case FBullet:
		ShootingFBullet(pos, angle, vo);
		break;
	case LBullet:
		ShootingLBullet(pos, angle, vo);
		break;
	}
}

CollisionDirection CPlayerWaepon::CheckCollision(CObject* obj)
{
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			//Kiểm tra va chạm với 1 đối tượng

			//Xử lý va chạm
		}

		//Loại bỏ những viên đạn đã va chạm với đối tượng
		RemoveBullet();
	}

	return NoCollision;
}

void CPlayerWaepon::Update(int delta_time)
{
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			CBullet* bullet = (*i).second;
			bullet->Update(delta_time);

			//Kiểm tra đạn có nằm trong màn hình không
			if (!CheckBulletInView(bullet->_physical.x, bullet->_physical.y))
			{
				_id_bullet[(*i).first] = 0;
			}
		}

		//Xóa những viên đạn không nằm trong màn hình
		RemoveBullet();
	}
}

void CPlayerWaepon::Draw()
{
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			(*i).second->Draw();
		}
	}
}

//Support
void CPlayerWaepon::ShootingNBullet(D3DXVECTOR3 pos, int angle, float vo)
{
	if (_list_bullet.size() < _max_count)
	{
		CBullet* bullet = new CNBullet(pos, angle, BULLET_N_V + _v_powerful, vo);
		bullet->LoadResources();

		int i = 0;
		while (i < _max_count)
		{
			if (_id_bullet[i] == 0)
			{
				_id_bullet[i] = 1;
				_list_bullet[i] = bullet;
				break;
			}
			i++;
		}
	}
}

void CPlayerWaepon::ShootingMBullet(D3DXVECTOR3 pos, int angle, float vo)
{
	if (_list_bullet.size() < _max_count)
	{
		CBullet* bullet = new CMBullet(pos, angle, BULLET_M_V + _v_powerful, vo);
		bullet->LoadResources();

		int i = 0;
		while (i < _max_count)
		{
			if (_id_bullet[i] == 0)
			{
				_id_bullet[i] = 1;
				_list_bullet[i] = bullet;
				break;
			}
			i++;
		}
	}
}

void CPlayerWaepon::ShootingFBullet(D3DXVECTOR3 pos, int angle, float vo)
{
	if (_list_bullet.size() < _max_count)
	{
		CBullet* bullet = new CFBullet(pos, angle, BULLET_F_V + _v_powerful, vo);
		bullet->LoadResources();

		int i = 0;
		while (i < _max_count)
		{
			if (_id_bullet[i] == 0)
			{
				_id_bullet[i] = 1;
				_list_bullet[i] = bullet;
				break;
			}
			i++;
		}
	}

}

void CPlayerWaepon::ShootingLBullet(D3DXVECTOR3 pos, int angle, float vo)
{
	//Xóa tất cả đạn trong list
	if (_list_bullet.size() > 0)
	{
		for (map<int, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			CBullet* bullet = (*i).second;
			_id_bullet[(*i).first] = 0;
			delete bullet;
		}

		_list_bullet.clear();
	}

	//Tạo lại list đạn
	float _add_x = cos(D3DXToRadian(angle)) * BULLET_L_ELAPSED_DIS;
	float _add_y = sin(D3DXToRadian(angle)) * BULLET_L_ELAPSED_DIS;
	for (int i = 0; i < _max_count; i++)
	{
		float x = pos.x + _add_x*i;
		float y = pos.y + _add_y*i;
		D3DXVECTOR3 position = D3DXVECTOR3(x, y, 0);
		CBullet* bullet = new CLBullet(position, angle, BULLET_L_V + _v_powerful, vo);
		bullet->LoadResources();
		_list_bullet[i] = bullet;
		_id_bullet[i] = 1;
	}
}

void CPlayerWaepon::ShootingSBullet(D3DXVECTOR3 pos, int angle, float vo)
{
	if (_list_bullet.size() < _max_count)
	{
		int _count = 0;
		for (int i = 0; i < _max_count; i++)
		{
			//1 phát bắn chỉ đạt được tốt đa 5 viên đạn
			if (_count == BULLET_S_COUNT_ONE_SHOOT) break;

			//Kiểm tra trên băng đạn viên đạn nào vẫn chưa được bắn
			if (_id_bullet[i] == 0)
			{
				int _mid = BULLET_S_COUNT_ONE_SHOOT / 2;
				int _angle = (i % BULLET_S_COUNT_ONE_SHOOT - _mid) * BULLET_S_ELAPSED_DEGREES + angle;
				CBullet* bullet = new CSBullet(pos, _angle, BULLET_S_V + _v_powerful, vo);
				bullet->LoadResources();
				_list_bullet[i] = bullet;
				_id_bullet[i] = 1;
				_count++;
			}
		}
	}
}

void CPlayerWaepon::RemoveBullet()
{
	for (int i = 0; i < _max_count; i++)
	{
		if (_id_bullet[i] == 0)
		{
			CBullet* bullet = _list_bullet[i];
			_list_bullet.erase(i);
			delete bullet;
		}
	}
}