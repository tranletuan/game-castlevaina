#include "CPlayerWaepon.h"

CPlayerWaepon::CPlayerWaepon()
{
	_player_waepon_type = NBullet;
}

CPlayerWaepon::~CPlayerWaepon()
{
	CWaeponFactory::~CWaeponFactory();
}

void CPlayerWaepon::SetWaeponType(PlayerWaeponType type)
{
	this->_player_waepon_type = type;
}

void CPlayerWaepon::Shooting(D3DXVECTOR3 pos, int angle, float direction)
{
	
}

CollisionDirection CPlayerWaepon::CheckCollision(CObject* obj)
{
	if (_list_bullet.size() > 0)
	{
		for (map<string, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			(*i).second->_is_enable = false;
		}
	}
}

void CPlayerWaepon::Update(int delta_time)
{
	if (_list_bullet.size() > 0)
	{
		for (map<string, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			(*i).second->Update(delta_time);
		}
	}
}

void CPlayerWaepon::Draw()
{
	if (_list_bullet.size() > 0)
	{
		for (map<string, CBullet*>::iterator i = _list_bullet.begin(); i != _list_bullet.end(); i++)
		{
			(*i).second->Draw();
		}
	}
}

//Support
void CPlayerWaepon::ShootingNBullet(D3DXVECTOR3 pos, int angle, float direction)
{

}

void CPlayerWaepon::ShootingMBullet(D3DXVECTOR3 pos, int angle, float direction)
{

}

void CPlayerWaepon::ShootingLBullet(D3DXVECTOR3 pos, int angle, float direction)
{

}

void CPlayerWaepon::ShootingFBullet(D3DXVECTOR3 pos, int angle, float direction)
{

}

void CPlayerWaepon::ShootingSBullet(D3DXVECTOR3 pos, int angle, float direction)
{

}
