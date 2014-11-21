#ifndef CAMERA_H
#define CAMERA_H

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"


class CCamera
{

public:
	D3DXVECTOR2 view_port;
	CCamera();
	CCamera(float posX, float posY);

	void UpdateCamera(float x);
	void UpdateCameraY(float y);
	D3DXVECTOR3 CenterSprite(int x, int y, int width, int height);
	D3DXVECTOR3 Transform(float x, float y);
	D3DXVECTOR3 Transform(D3DXVECTOR3 pos);

	float getPosX(){ return view_port.x; }
	float getPosY(){ return view_port.y; }
	int getWidth(){ return kScreenWidth; }
	int getHeight(){ return kScreenHeight; }
};


#endif