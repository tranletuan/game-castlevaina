#ifndef _CBILL_H_
#define _CBILL_H_

#include "IMovableObject.h"
#include "CObject.h"
#include "Config.h"

enum Environment
{
	Land, Water
};

enum GunDirection
{
	Normal, Up, Down
};

enum PlayerStatus
{
	Move, Stand, Jump, Die, Fall
};

class CBill : public IMovableObject, public CObject
{
protected:
	CSprite* _bill_stand;
	CSprite* _bill_jump;
	CSprite* _bill_die;
	CSprite* _bill_move;
	CSprite* _bill_in_water;

	Environment _enviroment;
	GunDirection _gun_direction;
	PlayerStatus _player_status;

	void DrawWhenMove(D3DXVECTOR3 pos);
	void DrawWhenStand(D3DXVECTOR3 pos);
	void DrawWhenJump(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenAttack(D3DXVECTOR3 pos);

public:
	CBill(int id, SpecificType specific_type, D3DXVECTOR3 pos);
	~CBill();

	void LoadResources();
	void Draw();
	void Update(int delta_time);
	void SetStatus(PlayerStatus stt);
	void SetEnviroment(Environment env);
	void SetGunDirection(GunDirection gd);

	void Moving(float vx);
	void Standing();
	void Jumping();
	void Attacking();
	void Dying();
};

#endif // !_CBILL_H_
