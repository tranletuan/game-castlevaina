#ifndef CWATERFALL_H
#define CWATERFALL_H

#include "CGround.h"

class CWaterFall
	: public CGround
{
private:
	int _cols; // so cot
	int _rows; // so dong
	int _countTime; 
public:
	CWaterFall(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CWaterFall();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

};

#endif