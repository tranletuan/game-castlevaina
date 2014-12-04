#ifndef _CPLAYER_WAEPON_H_
#define _CPLAYER_WAEPON_H_

#include "CWeapon.h"
#include "CSBullet.h"
#include "CNBullet.h"
#include "CFBullet.h"
#include "CLBullet.h"
#include "CMBullet.h"

enum PlayerWeaponType
{
	WPN, WPM, WPS, WPF, WPL
};

class CPlayerWeapon : public CWeapon
{
private:
	float _v_powerful;
	PlayerWeaponType _player_waepon_type;

	bool ShootingNBullet(D3DXVECTOR3 pos, int angle, float vo);
	bool ShootingMBullet(D3DXVECTOR3 pos, int angle, float vo);
	bool ShootingLBullet(D3DXVECTOR3 pos, int angle, float vo);
	bool ShootingFBullet(D3DXVECTOR3 pos, int angle, float vo);
	bool ShootingSBullet(D3DXVECTOR3 pos, int angle, float vo);

	queue<CBullet*> _queue_bullet_n;
	queue<CBullet*> _queue_bullet_m;
	queue<CBullet*> _queue_bullet_s;
	queue<CBullet*> _queue_bullet_f;
	queue<CBullet*> _queue_bullet_l;

public:
	CPlayerWeapon();
	~CPlayerWeapon();
	void LoadResources();

	void SetWaeponType(PlayerWeaponType type);
	void SetVelocityPowerful(float vp);

	bool Shooting(D3DXVECTOR3 pos, int angle, float vo);
	void RemoveDisabledBullet();

	CollisionDirection CheckCollision(CObject* obj);
	PlayerWeaponType GetWeaponType();
};

#endif // !_CPLAYER_WAEPON_H_
