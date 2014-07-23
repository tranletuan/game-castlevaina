#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "sprite.h"
#include "global.h"

class Camera
{
public:
	
	D3DXVECTOR2 view_port;
	Camera();
	void UpdateCamera(int x);
	D3DXVECTOR3 Transform(int x, int y);
};

#endif // !_CAMERA_H_
