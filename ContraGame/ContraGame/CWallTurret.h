#ifndef _CWALL_TURRET_H_
#define _CWALL_TURRET_H_

#include "CEnemyUseGun.h"

class CWallTurret : public CEnemyUseGun
{
protected:
	bool _ready_shoot;
	bool _can_shoot;
	int _real_angle;
	float _x_shoot;
	float _y_shoot;

	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenWait(D3DXVECTOR3 pos);
	void Attacking();
	bool CheckCorrectAngle();
	int GetIndexSpriteByAngle(int angle);
	void ChangeRealAngle();
	void ChangeShootPosition(int angle);

public:
	CWallTurret(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CWallTurret();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetTarget(float x, float y);

};
#endif // !_CWALL_TURRET_H_
