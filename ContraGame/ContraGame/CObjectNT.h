#ifndef COBJECTNT_H
#define COBJECTNT_H

#include "CObject.h"

class CObjectNT:
	public CObject
{

private:
	int _way; // quy dao di cua ob

public:
	CObjectNT(int id, SpecificType specific_type, BasicType basic_type, D3DXVECTOR3 pos,int way , int width = 0, int height = 0);
	~CObjectNT();

};



#endif