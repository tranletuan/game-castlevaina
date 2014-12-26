#ifndef _PHYSICAL_H_
#define _PHYSICAL_H_

#include <Windows.h>
#include <math.h>
#include "Config.h"

enum CollisionDirection
{
	NoCollision, LeftCollision, RightCollision, TopCollision, BottomCollision, Undefined
};

struct BOUNDS
{
	float left, right, top, bottom;
	float width = 0, height = 0;
};

class CPhysical
{
public:
	float	x;
	float	y;
	float	vx;
	float	vy;
	float	n; //Phản lực n trong trường hợp gia chạm với mắt đất
	float	vx_last;
	float	vx_accretion;
	int		_width;
	int		_height;
	BOUNDS	bounds;
	DWORD	time_in_space;

	float	current_vx;
	float	current_vy;

	CPhysical();
	CPhysical(float x, float y, float vx = 0, float vy = 0);
	~CPhysical();

	void SetBounds(float x, float y, float width = 0, float height = 0);
	void CalcPositionWithGravitation(int time, float gravity);
	void CalcPositionWithoutGravitation(int time);
	CollisionDirection Collision(CPhysical* physical);

private:
	bool CheckBounds(CPhysical* physical);
	void Swap(float &Dentry, float &Dexit);
	float Max(float a, float b);
	float Min(float a, float b);
	float CalcD(float S, float M);
	float CalcTEntry(float Dentry, float V);
	float CalcTExit(float Dexit, float V);
	CollisionDirection CollisionX(float &dx_entry, float &dx_exit, float &tx_entry, float &tx_exit, CPhysical* physical);
	CollisionDirection CollisionY(float &dy_entry, float &dy_exit, float &ty_entry, float &ty_exit, CPhysical* physical);

};
#endif