#ifndef _CBOSS2_H_
#define _CBOSS2_H_

#include "CBoss2Arm.h"

enum Boss2Status
{
	B2Prepare, B2Wait, B2Attack, B2Die
};

class CBoss2 : public CObject
{
protected:
	CBoss2Arm* _left_arm;
	CBoss2Arm* _right_arm;
	
	CSprite* _live_sprite;
	CSprite* _die_sprite;
	CSprite* _destroy_sprite;

	CEnemyWeapon* _weapon;
	queue<int> _queue_id_bullet;
	
	Boss2Status _status;

	void DrawWhenWait(D3DXVECTOR3 pos);
	void DrawWhenPrepare(D3DXVECTOR3 pos);
	void DrawWhenAttack(D3DXVECTOR3 pos);
	void DrawWhenDie(D3DXVECTOR3 pos);

	void Attacking();

public:
	CBoss2(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CBoss2();

	void LoadResources();
	void Update(int time);
	void Draw();
	vector<CPhysical> GetListElement();
};
#endif // !_CBOSS2_H_
