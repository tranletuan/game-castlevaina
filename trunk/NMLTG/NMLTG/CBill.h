#ifndef _CBILL_H_
#define _CBILL_H_

#include "CMovableObject.h"

enum Environment
{
	Ground, Water
};

enum GunDirection
{
	Normal, Up, Down
};

class CBill : public CMovableObject
{
protected:
	CSprite* _bill_stand;
	CSprite* _bill_jump;
	CSprite* _bill_die;
	CSprite* _bill_move;
	CSprite* _bill_in_water;
	Environment _enviroment;
	GunDirection _gun_direction;

	void DrawWhenMove(D3DXVECTOR3 pos);
	void DrawWhenStand(D3DXVECTOR3 pos);
	void DrawWhenJump(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenAttack(D3DXVECTOR3 pos);

public:
	CBill(D3DXVECTOR3 pos, int size);
	~CBill();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetStatus(Status stt);
	void SetEnviroment(Environment env);
	void SetGunDirection(GunDirection gd);

	void MovingLeft();
	void MovingRight();
	void Standing();
	void Jumping();
	void Attacking();
	void Dying();
};

#endif // !_CBILL_H_
