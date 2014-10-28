#ifndef _IMOVABLE_OBJECT_H_
#define _IMOVABLE_OBJECT_H_

class IMovableObject
{

public:
	virtual void Update(int delta_time) = 0;
	virtual void Moving(float vx) = 0;
};
#endif