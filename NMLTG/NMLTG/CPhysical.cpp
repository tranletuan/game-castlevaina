#include "CPhysical.h"

CPhysical::CPhysical()
{
	this->x = 0;
	this->y = 0;
	this->vx = 0;
	this->vy = 0;
	this->vx_last = 1.0f;
	this->current_vx = 0;
	this->current_vy = 0;
	this->time_in_space = 0;
	this->n = 0;
}

CPhysical::CPhysical(float x, float y, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->vx_last = 1.0f;
	this->n = 0;
	this->time_in_space = 0;
	this->current_vx = 0;
	this->current_vy = 0;
}

void CPhysical::SetBounds(float x, float y, float width, float height)
{
	bounds.left = x - width / 2;
	bounds.right = bounds.left + width;
	bounds.top = y + height / 2;
	bounds.bottom = bounds.top - height;
}

void CPhysical::CalcPositionWithGravitation(int time, float gravity)
{
	current_vx = vx * time;
	x += current_vx;
	
	//Chỉ bắt đầu rơi khi đối tượng chưa rơi
	//Tức là khi đang rơi (time_in_space != 0) thì k set thời gian rơi
	if (time_in_space == 0)
	{
		time_in_space = GetTickCount();
	}

	if (time_in_space > 0)
	{
		DWORD current_time = GetTickCount() - time_in_space + 64;
		current_vy = vy - gravity * current_time;
		y += current_vy + n * current_time;
	}
}

void CPhysical::CalcPositionWithoutGravitation(int time)
{
	current_vx = vx * time;
	x += current_vx;

	current_vy = vy * time;
	y += current_vy;
}

CollisionDirection CPhysical::Collision(CPhysical* physical)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_exit, ty_entry, ty_exit, dy_entry;

	CollisionDirection cdx = CollisionX(dx_entry, dx_exit, tx_entry, tx_exit, physical);
	CollisionDirection cdy = CollisionY(dy_entry, dy_exit, ty_entry, ty_exit, physical);

	//Trường hợp 1 trong 2 trục x và y k có va chạm thì 2 vật k va chạm
	if (cdx == NoCollision || cdy == NoCollision) return NoCollision;

	//Trường hợp cả vx và vy = 0 
	if (cdx != Undefined && cdy != Undefined)
		return (dx_entry <= dy_entry ? cdx : cdy);

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
	
	if (v == 0 ||(bounds.right >=  physical->bounds.left && bounds.left <= physical->bounds.right))
	{
		if (bounds.left <= physical->bounds.right &&
			bounds.left >= physical->bounds.left - (bounds.right - bounds.left))
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
	//Trường hợp vector vận tốc giữa 2 vật != 0
	else if (v != 0)
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
}

CollisionDirection CPhysical::CollisionY(float &dy_entry, float &dy_exit, float &ty_entry, float &ty_exit, CPhysical* physical)
{
	float v = current_vy - physical->current_vy;
	
	if (v == 0 || (bounds.top >= physical->bounds.bottom && bounds.bottom <= physical->bounds.top))
	{
		if (bounds.bottom <= physical->bounds.top &&
			bounds.bottom >= physical->bounds.bottom - (bounds.top - bounds.bottom))
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
	//Trường hợp tọa độ y của vật di chuyển
	else if (v != 0)
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
}
