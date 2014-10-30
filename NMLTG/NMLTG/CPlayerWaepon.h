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
	PlayerWaeponType _player_waepon_type;
	void ShootingNBullet(D3DXVECTOR3 pos, int angle, float direction);
	void ShootingMBullet(D3DXVECTOR3 pos, int angle, float direction);
	void ShootingLBullet(D3DXVECTOR3 pos, int angle, float direction);
	void ShootingFBullet(D3DXVECTOR3 pos, int angle, float direction);
	void ShootingSBullet(D3DXVECTOR3 pos, int angle, float direction);
public:
	CPlayerWaepon();
	~CPlayerWaepon();
	void SetWaeponType(PlayerWaeponType type);

	void Shooting(D3DXVECTOR3 pos, int angle, float direction);
	CollisionDirection CheckCollision(CObject* obj);
	void Update(int delta_time);
	void Draw();
};

#endif // !_CPLAYER_WAEPON_H_
