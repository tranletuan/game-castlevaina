#ifndef _SIMON_H_
#define _SIMON_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "sprite.h"
#include "camera.h"

#define VECTOR_V 0.045f
#define VECTOR_G 0.11f

enum Status
{
	SIMON_STAND, SIMON_MOVE_LEFT, SIMON_MOVE_RIGHT, SIMON_DIE,
	SIMON_MOVE_UP, SIMON_STOOP, SIMON_JUMP,
	SIMON_USE_CANE, SIMON_STOOP_USE_CANE, SIMON_USE_ITEM
};

class Simon
{
protected:
	int i = 0;
	Sprite *sprite_normal;
	float vx, vy, vx_last;
	Status status;

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
	//Điều khiển
	void Stand();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void Jump();
	void Stoop();

};
#endif // !_SIMON_H_
