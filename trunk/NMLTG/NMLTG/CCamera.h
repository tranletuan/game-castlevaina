#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"
#include "CSprite.h"

class CCamera
{
public:
	
	D3DXVECTOR2 view_port;
	CCamera();

	void UpdateCamera(float x);
	D3DXVECTOR3 CenterSprite(int x, int y, int width, int height);
	D3DXVECTOR3 Transform(float x, float y);
	D3DXVECTOR3 Transform(D3DXVECTOR3 pos);
};

#endif // !_CAMERA_H_
