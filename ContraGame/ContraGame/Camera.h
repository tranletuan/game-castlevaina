#ifndef CAMERA_H
#define CAMERA_H

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"
#include "CResourcesManager.h"

enum CamState
{
	CamS_Move, // tự đông di chuyển
	CamS_Follow, // theo con bill
	CamS_Stop // dừng lại
};
class CResourcesManager;
class CCamera
{
private:
	CamState _state;	
	float _vX; // Vận tốc vX
	float _vY;
	float _distanceX; // khoảng di chuyển theo X
	

public:
	D3DXVECTOR2 view_port;
	CCamera();
	CCamera(float posX, float posY);

	void UpdateCameraX(float x);
	void UpdateCameraY(float y);
	void Update(int time);
	D3DXVECTOR3 CenterSprite(int x, int y, int width, int height);
	D3DXVECTOR3 Transform(float x, float y);
	D3DXVECTOR3 Transform(D3DXVECTOR3 pos);

	void processInput();

	float getPosX(){ return view_port.x; }
	float getPosY(){ return view_port.y; }
	int getWidth(){ return kScreenWidth; }
	int getHeight(){ return kScreenHeight; }	
	void setVx(float x){ _vX = 0; }
	float getVx(){ return _vX; }
	void setState(CamState x){ _state = x; }
	CamState getState(){ return _state; }

	void MoveX( int time); // Di chuyển  theo X
	void MoveY(int time); // Di chuyển  theo Y
};


#endif