#include "CPhysical.h"

CPhysical::CPhysical()
{
}

CPhysical::CPhysical(float x, float y, int width, int height, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->width = width;
	this->height = height;
	this->vx_last = 1.0f;
}

void CPhysical::UpdateVelocityX(int time)
{
	x += vx * time;
}

void CPhysical::UpdateVelocityY(int time)
{
	DWORD current_time = GetTickCount() - time_start_jump + 1;
	y += vy - GRAVITY * current_time;
}

CollisionDirection CPhysical::Collision(CPhysical* physical)
{
	if (CheckBoundsCollision(physical) == true)
	{
		CollisionX(physical);
		CollisionY(physical);

		entry_time = Max(dx_entry, dy_entry);
		exit_time = Min(dx_exit, dy_exit);

		//Điều kiện xảy ra va chạm 
		if (entry_time < exit_time && entry_time < 1 && entry_time > 0)
		{
			if (tx_entry > ty_entry)
			{
				if (tx_entry < 0)
				{
					return CollisionDirection::right;
				}
				else
				{
					return CollisionDirection::left;
				}
			}
			else 
			{
				//trường hợp tx và ty bằng nhau (va chạm vào góc)
				//thì xem như va chạm này là ở bên trên hoặc bên dưới
				if (ty_entry < 0)
				{
					return CollisionDirection::top;
				}
				else
				{
					return CollisionDirection::botton;
				}
			}
		}
		else
		{
			return CollisionDirection::NoCollision;
		}
	}
}

//SUPPORT METHOD
bool CPhysical::CheckBoundsCollision(CPhysical* physical)
{
	bool flag = true;

	return flag;
}

void CPhysical::Swap(float &Dentry, float &Dexit)
{
	int temp = Dentry;
	Dentry = Dexit;
	Dexit = temp;
}

float CPhysical::CalcDEntry(int Sx, int Mx, int Ml)
{
	return Sx - (Mx + Ml);
}

float CPhysical::Max(float a, float b)
{
	return a > b ? a : b;
}

float CPhysical::Min(float a, float b)
{
	return a < b ? a : b;
}

float CPhysical::CalcDExit(int Sx, int Sl, int Mx)
{
	return (Sx + Sl) - Mx;
}

void CPhysical::CollisionX(CPhysical* physical)
{
	dx_entry = CalcDEntry(physical->x, x, width);
	dx_exit = CalcDExit(physical->x, physical->width, x);
	float v = vx - physical->vx;

	if (v < 0)
	{
		Swap(dx_entry, dx_exit);
	}

	tx_entry = dx_entry / v;
	tx_exit = dx_exit / v;
}

void CPhysical::CollisionY(CPhysical* physical)
{
	dy_entry = CalcDEntry(physical->y, y, height);
	dy_exit = CalcDExit(physical->y, physical->width, y);
	float v = vy - physical->vy;

	if (v < 0)
	{
		Swap(dy_entry, dy_exit);
	}

	ty_entry = dy_entry / v;
	ty_exit = dy_exit / v;
}
