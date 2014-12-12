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
	CamState _cam_state;
	bool _isMove;
	bool _isStop;
	float _vX; // Vận tốc vX

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
	void setState(CamState x){ _cam_state = x; }
	CamState getState(){ return _cam_state; }

	void MoveDistanceX( float distance, int time); // Di chuyển 1 khoảng cách khi tới điểm theo X
};


#endif