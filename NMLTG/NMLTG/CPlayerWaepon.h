#ifndef _CPLAYER_WAEPON_H_
#define _CPLAYER_WAEPON_H_

#include "CWaeponFactory.h"
#include "CSBullet.h"
#include "CNBullet.h"
#include "CFBullet.h"
#include "CLBullet.h"
#include "CMBullet.h"

enum PlayerWaeponType
{
	NBullet, MBullet, SBullet, FBullet, LBullet
};

class CPlayerWaepon : public CWaeponFactory
{
private:
	int _id_bullet[BULLET_S_COUNT];
	int _max_count;
	float _v_powerful;
	PlayerWaeponType _player_waepon_type;
	void ShootingNBullet(D3DXVECTOR3 pos, int angle, float vo);
	void ShootingMBullet(D3DXVECTOR3 pos, int angle, float vo);
	void ShootingLBullet(D3DXVECTOR3 pos, int angle, float vo);
	void ShootingFBullet(D3DXVECTOR3 pos, int angle, float vo);
	void ShootingSBullet(D3DXVECTOR3 pos, int angle, float vo);
public:
	CPlayerWaepon();
	~CPlayerWaepon();
	void SetWaeponType(PlayerWaeponType type);
	void SetVelocityPowerful(float vp);

	void Shooting(D3DXVECTOR3 pos, int angle, float vo);
	CollisionDirection CheckCollision(CObject* obj);
	void Update(int delta_time);
	void Draw();
	void RemoveBullet();
};

#endif // !_CPLAYER_WAEPON_H_
