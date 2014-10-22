#include "CPhysical.h"

CPhysical::CPhysical()
{
}

CPhysical::CPhysical(float x, float y, float width, float height, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->width = width;
	this->height = height;
	this->vx_last = 1.0f;
	this->bounds = SetBounds(x, y, width, height);
}

void CPhysical::UpdateVelocity(int time)
{
	current_vx = vx * time;
	x += current_vx;

	current_vy = vy * time;
	y += current_vy;

	/*if (time_in_space > 0)
	{
		DWORD current_time = GetTickCount() - time_in_space + 1;
		current_vy = vy - GRAVITY * current_time;
		y += current_vy;
	}*/

	this->bounds = SetBounds(x, y, width, height);
}

CollisionDirection CPhysical::Collision(CPhysical* physical)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_exit, ty_entry, ty_exit;

	CollisionDirection cdx = CollisionX(dx_entry, dx_exit, tx_entry, tx_exit, physical);
	CollisionDirection cdy = CollisionY(dy_entry, dy_exit, ty_entry, ty_exit, physical);

	//Trường hợp 1 trong 2 trục x và y k có va chạm thì 2 vật k va chạm
	if (cdx == NoCollision || cdy == NoCollision) return NoCollision;

	//Trường hợp cả vx và vy = 0 
	if (cdx != Undefined && cdy != Undefined) return (dx_entry <= dy_entry ? cdx : cdy);

	//Trường hợp đã va chạm trục y và vy = 0 
	if (cdx == Undefined && cdy != Undefined)
	{
		if (tx_entry < tx_exit && (tx_entry > 0 && tx_entry < 1))
		{
			if (dx_entry < 0) return RightCollision;
			else return LeftCollision;
		}
	}
	//Trường hợp đã va chạm trục x và vx = 0
	else if (cdx != Undefined && cdy == Undefined)
	{
		if (ty_entry < ty_exit && (ty_entry > 0 && ty_entry < 1))
		{
			if (dy_entry < 0) return TopCollision;
			else return BottomCollision;
		}
	}
	//Trường hợp chưa va chạm và vx, vy đều != 0
	else
	{
		float entry_time = Max(tx_entry, ty_entry);
		float exit_time = Min(tx_exit, ty_exit);

		if (entry_time < exit_time && (entry_time > 0 && entry_time < 1))
		{
			if (tx_entry > ty_entry)
			{
				if (dx_entry < 0) return RightCollision;
				else return LeftCollision;
			}
			else
			{
				if (dy_entry < 0) return TopCollision;
				else return BottomCollision;
			}
		}
	}

	return NoCollision;
}

//SUPPORT METHOD
BOUNDS CPhysical::SetBounds(float centerX, float centerY, float width, float height)
{
	BOUNDS rect;

	rect.left = centerX - width / 2;
	rect.right = rect.left + width;
	rect.top = centerY + height / 2;
	rect.bottom = rect.top - height;

	return rect;
}

bool CPhysical::CheckBoundsCollision(CPhysical* physical)
{
	bool flag = true;

	return flag;
}

void CPhysical::Swap(float &Dentry, float &Dexit)
{
	float temp = Dentry;
	Dentry = Dexit;
	Dexit = temp;
}

float CPhysical::CalcD(float S, float M)
{
	return S - M;
}

float CPhysical::Max(float a, float b)
{
	return a > b ? a : b;
}

float CPhysical::Min(float a, float b)
{
	return a < b ? a : b;
}

CollisionDirection CPhysical::CollisionX(float &dx_entry, float &dx_exit, float &tx_entry, float &tx_exit, CPhysical* physical)
{
	float v = current_vx - physical->current_vx;
	
	//Trường hợp vector vận tốc giữa 2 vật != 0
	if (v != 0)
	{
		dx_entry = CalcD(physical->bounds.left, bounds.right);
		dx_exit = CalcD(physical->bounds.right, bounds.left);

		if (v < 0)
		{
			Swap(dx_entry, dx_exit);
		}

		tx_entry = dx_entry / v;
		tx_exit = dx_exit / v;

		return Undefined;
	}
	else //Trường hợp vector vận tốc giữa 2 vật = 0
	{
		if (bounds.left <= physical->bounds.right &&
			bounds.left >= physical->bounds.left - width)
		{
			if (bounds.left <= physical->bounds.left)
			{
				dx_entry = bounds.right - physical->bounds.left;
				return LeftCollision;
			}
			else
			{
				dx_entry = physical->bounds.right - bounds.left;
				return RightCollision;
			}
		}
		else
		{
			return NoCollision;
		}
	}
}

CollisionDirection CPhysical::CollisionY(float &dy_entry, float &dy_exit, float &ty_entry, float &ty_exit, CPhysical* physical)
{
	float v = current_vy - physical->current_vy;
	
	//Trường hợp tọa độ y của vật di chuyển
	if (v != 0)
	{
		dy_entry = CalcD(physical->bounds.bottom, bounds.top);
		dy_exit = CalcD(physical->bounds.top, bounds.bottom);

		if (v < 0)
		{
			Swap(dy_entry, dy_exit);
		}

		ty_entry = dy_entry / v;
		ty_exit = dy_exit / v;

		return Undefined;
	}
	//Trường hợp tọa độ y của vật đứng yên hoặc vận tốc quá nhỏ
	else 
	{
		if (bounds.bottom <= physical->bounds.top &&
			bounds.bottom >= physical->bounds.bottom - height)
		{
			if (bounds.bottom <= physical->bounds.bottom)
			{
				dy_entry = bounds.top - physical->bounds.bottom;
				return BottomCollision;
			}
			else
			{
				dy_entry = physical->bounds.top - bounds.bottom;
				return TopCollision;
			}
		}
		else
		{
			return NoCollision;
		}
	}
}
