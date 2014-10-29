#ifndef _PHYSICAL_H_
#define _PHYSICAL_H_

#include <Windows.h>
#include <math.h>

#define GRAVITY 0.07f
#define MIN_V 1.1f

enum CollisionDirection
{
	NoCollision, LeftCollision, RightCollision, TopCollision, BottomCollision, Undefined
};

struct BOUNDS
{
	float left, right, top, bottom;
};

class CPhysical
{
public:
	float	x;
	float	y;
	float	width;
	float	height;
	float	vx;
	float	vy;
	float	vx_last;
	BOUNDS	bounds;
	DWORD	time_in_space;

	float	current_vx;
	float	current_vy;

	CPhysical();
	CPhysical(float x, float y, float width = 0, float height = 0, float vx = 0, float vy = 0);

	void CalcPositionWithGravitation(int time);
	void CalcPositionWithoutGravitation(int time);
	CollisionDirection Collision(CPhysical* physical);
	
private:
	BOUNDS SetBounds(float centerX, float centerY, float width, float height);
	bool CheckBoundsCollision(CPhysical* physical);
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