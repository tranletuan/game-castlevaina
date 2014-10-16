#ifndef _MOVABLE_OBJECT_H_
#define _MOVABLE_OBJECT_H_

#include "CObject.h"

enum Status
{
	Move, Stand, Jump, Attack, Die
};

class CMovableObject : public CObject
{
protected:
	Status _status;

public:
	virtual void LoadResources() = 0;
	virtual void Draw() = 0;
	virtual void Update(int delta_time) = 0;

	virtual void MovingLeft() = 0;
	virtual void MovingRight() = 0;
	virtual void Standing() = 0;
	virtual void Jumping() = 0;
	virtual void Attacking() = 0;
	virtual void Dying() = 0;

};
#endif