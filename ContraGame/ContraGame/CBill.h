#ifndef _CBILL_H_
#define _CBILL_H_

#include "CObject.h"
#include "Config.h"
#include "CPlayerWeapon.h"
#include "Input.h"

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

class CBill : public CObject
{
protected:
	CInput *_input;
	CPlayerWeapon* _weapon;
	CAudio *_audio;


	CSprite* _bill_stand;
	CSprite* _bill_jump;
	CSprite* _bill_die;
	CSprite* _bill_move;
	CSprite* _bill_in_water;

	Environment _enviroment;
	
	PlayerStatus _player_status;
	DWORD _last_time_revival;
	DWORD _last_time_die;
	DWORD _last_time_wait;
	DWORD _last_time_shoot;

	float	_x_last;
	float	_y_last;
	int		_count_jump;
	bool	_is_wait;
	bool	_is_revival;
	int		_revival_time;
	int		_id_ground_stand;
	void UpdateBounds();
	bool SetStatus(PlayerStatus status);
	void DrawWhenMove(D3DXVECTOR3 pos);
	void DrawWhenStand(D3DXVECTOR3 pos);
	void DrawWhenJump(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void OnKeyDown();
	void OnKeyUp();
	void IsKeyDown();

public:
	CBill(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	CBill();
	~CBill();

	GunDirection _gun_direction;
	bool _mission_complete;
	void LoadResources();
	void Draw();
	void Update(int delta_time);

	void SetEnviroment(Environment env);
	void SetGunDirection(GunDirection gd);
	void SetWeapon(CPlayerWeapon* weapon) { _weapon = weapon; }

	void Dying();
	void Jumping();
	void Attacking();
	void Moving(float vx);
	void Standing(float y_ground, int id_ground);
	bool Falling(CObject* ground);
	void Living();
	void GoingToNext();
	void Undying();

	int GetIdGroundIgnore();
	int	GetGunDirection();

	void ProcessInput();

};

#endif // !_CBILL_H_
