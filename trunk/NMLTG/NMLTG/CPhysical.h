#ifndef _PHYSICAL_H_
#define _PHYSICAL_H_

#include <Windows.h>

#define GRAVITY 0.07f

enum CollisionDirection
{
	NoCollision, left, right, top, botton
};

class CPhysical
{
public:
	int		x;
	int		y;
	int		width;
	int		height;
	float	vx;
	float	vy;
	float	vx_last;
	int		ground;
	DWORD	time_start_jump;

	float	dx_entry;
	float	tx_entry;
	float	dx_exit;
	float	tx_exit;

	float	dy_entry;
	float	ty_entry;
	float	dy_exit;
	float	ty_exit;
	
	float	entry_time;
	float	exit_time;

	CPhysical();
	CPhysical(float x, float y, int width = 0, int height = 0, float vx = 0, float vy = 0);

	void UpdateVelocityY(int time);
	void UpdateVelocityX(int time);
	CollisionDirection Collision(CPhysical* physical);
private:
	bool CheckBoundsCollision(CPhysical* physical);
	void Swap(float &Dentry, float &Dexit);
	float Max(float a, float b);
	float Min(float a, float b);
	float CalcDEntry(int Sx, int Mx, int Ml);
	float CalcDExit(int Sx, int Sl, int Mx);
	float CalcTEntry(float Dentry, float V);
	float CalcTExit(float Dexit, float V);
	void CollisionX(CPhysical* physical);
	void CollisionY(CPhysical* physical);
};
#endif