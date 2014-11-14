#ifndef _CPLAYER_WAEPON_H_
#define _CPLAYER_WAEPON_H_

#include "CWaepon.h"
#include "CSBullet.h"
#include "CNBullet.h"
#include "CFBullet.h"
#include "CLBullet.h"
#include "CMBullet.h"

enum PlayerWaeponType
{
	WPN, WPM, WPS, WPF, WPL
};

class CPlayerWaepon : public CWaepon
{
private:
	float _v_powerful;
	PlayerWaeponType _player_waepon_type;

	void ShootingNBullet(D3DXVECTOR3 pos, int angle, float vo);
	void ShootingMBullet(D3DXVECTOR3 pos, int angle, float vo);
	void ShootingLBullet(D3DXVECTOR3 pos, int angle, float vo);
	void ShootingFBullet(D3DXVECTOR3 pos, int angle, float vo);
	void ShootingSBullet(D3DXVECTOR3 pos, int angle, float vo);

	queue<CBullet*> _queue_bullet_n;
	queue<CBullet*> _queue_bullet_m;
	queue<CBullet*> _queue_bullet_s;
	queue<CBullet*> _queue_bullet_f;
	queue<CBullet*> _queue_bullet_l;

public:
	CPlayerWaepon();
	~CPlayerWaepon();
	void LoadResources();

	void SetWaeponType(PlayerWaeponType type);
	void SetVelocityPowerful(float vp);

	void Shooting(D3DXVECTOR3 pos, int angle, float vo);
	void RemoveDisabledBullet();

	CollisionDirection CheckCollision(CObject* obj);
	PlayerWaeponType GetWaeponType();
};

#endif // !_CPLAYER_WAEPON_H_
