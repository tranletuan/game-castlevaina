#ifndef CWATERFALL_H
#define CWATERFALL_H

#include "CEffectObject.h"

class CWaterFallE
	: public CEffectObject
{
private:
	int _cols; // so cot
	int _rows; // so dong
	int _countTime; 
public:
	CWaterFallE(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CWaterFallE();

	void LoadResources();
	void Draw();
	void Update(int delta_time);

};

#endif