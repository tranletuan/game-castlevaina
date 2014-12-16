#ifndef _CGROUNDSTAR_H_
#define _CGROUNDSTAR_H_

#include "CEffectObject.h"

class CStarEffect : public CEffectObject
{
private:
	int _count;
	int _time_count;
	bool _isDraw;
	
	int _indexSprite;
public:
	CStarEffect(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	~CStarEffect();

	void LoadResources();
	void Draw();
	void Update(int delta_time);


};
#endif // !_CGROUNDSTAR_H_
