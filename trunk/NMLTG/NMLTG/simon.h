#ifndef _SIMON_H_
#define _SIMON_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "sprite.h"
#include "camera.h"

class Simon
{
protected:
	Sprite *sprite_normal;
	Texture *texture;
	float vx, vy;
	
public:
	D3DXVECTOR2 pos;
	int heath;
	RECT simon_bounds;
	RECT cane_bounds;

	Simon(D3DXVECTOR2 pos);
	~Simon();
	void LoadResources();
	void Update(int delta);
	void Draw(Camera camera);
	

};
#endif // !_SIMON_H_
