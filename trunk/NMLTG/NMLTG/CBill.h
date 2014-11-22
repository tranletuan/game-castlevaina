#ifndef _CBILL_H_
#define _CBILL_H_

#include "IMovableObject.h"
#include "CObject.h"
#include "Config.h"
#include "CPlayerWeapon.h"

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
	Stand, Move, Attack, Jump, Fall, Die
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

	int _id_ground_stand;
	void UpdateBounds();
	bool SetStatus(PlayerStatus status);
	void DrawWhenMove(D3DXVECTOR3 pos);
	void DrawWhenStand(D3DXVECTOR3 pos);
	void DrawWhenJump(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenAttack(D3DXVECTOR3 pos);

public:
	CBill(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBill();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

	void SetEnviroment(Environment env);
	void SetGunDirection(GunDirection gd);

	void Dying();
	void Jumping();
	void Attacking(CPlayerWeapon* weapon);
	void Moving(float vx);
	void Standing(float y_ground, int id_ground);
	bool Falling(CObject* ground);

	int GetIdGroundIgnore();
	int	GetGunDirection();
};

#endif // !_CBILL_H_
