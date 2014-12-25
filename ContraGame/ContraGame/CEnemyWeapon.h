#ifndef _CENEMY_WAEPON_H_
#define _CENEMY_WAEPON_H_

#include "CWeapon.h"
#include "CNEBullet.h"
#include "CBBullet.h"
#include "CB2Bullet.h"
#include "CSPBullet.h"
#include "CPlayerWeapon.h"
#include "CBill.h"

class CEnemyWeapon : public CWeapon
{
protected:
	queue<CBullet*> _queue_bullet_ne;
	queue<CBullet*> _queue_bullet_b;
	queue<CBullet*> _queue_bullet_b2;
	queue<CBullet*> _queue_bullet_me;
	queue<CBullet*> _queue_bullet_sp;

public:
	CEnemyWeapon();
	~CEnemyWeapon();

	void LoadResources();
	void RemoveDisabledBullet();
	void CheckCollisionWithPlayer(CBill* player);
	void CheckCollisionWithGround(CObject* ground);
	void CheckCollisionWithWeaponPlayer(CPlayerWeapon* weapon);
	void UpdateQueueIdBullet(queue<int> &queue_id_bullet);

	int ShootingBulletNE(D3DXVECTOR3 pos, int angle, float vo);
	int ShootingBulletB(D3DXVECTOR3 pos);
	int ShootingBulletB2(D3DXVECTOR3 pos, int angle, float vo);
	int ShootingBulletME(D3DXVECTOR3 pos, int angle, float vo);
	int ShootingBulletSP(D3DXVECTOR3 pos, int angle, float vo);
};
#endif // !_CENEMY_WAEPON_H_
