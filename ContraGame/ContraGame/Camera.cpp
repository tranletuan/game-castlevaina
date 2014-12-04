﻿#include "Camera.h"

CCamera::CCamera()
{
	view_port.x = 0;
	view_port.y = kScreenHeight;
	
}

CCamera::CCamera(float posX, float posY)
{
	view_port.x = posX;
	view_port.y = posY;
}

void CCamera::UpdateCameraX(float x)
{
	
	view_port.x = (int)x - kScreenWidth / 2;
	if (view_port.x < 0)
	{
		view_port.x = 0;
	}
}

void CCamera::UpdateCameraY(float y)
{
	view_port.y = (int)y + kScreenHeight / 2;
	if (view_port.y < 0)
	{
		view_port.y = 0;
	}
}

void CCamera::Update()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	switch (rs->m_levelMap)
	{
	case 1:
		UpdateCameraX(rs->m_posBill.x);
		break;
	case 2:
		UpdateCameraY(rs->m_posBill.y);
		break;
	}
	rs->_camera = this;
}

//Hàm để chuyển tọa độ góc của đối tượng thành tọa đô tậm
//Dùng trong khởi tạo
D3DXVECTOR3 CCamera::CenterSprite(int x, int y, int width, int height)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(x + width / 2, y + height / 2, 0);
	return pos;
}

D3DXVECTOR3 CCamera::Transform(float x, float y)
{
	//Ma trận dùng để nhân transform view port
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -view_port.x;
	matrix._42 = view_port.y;

	//Tọa độ hiện tại
	D3DXVECTOR3 pos3(x, y, 0);
	D3DXVECTOR4 final_matrix;
	D3DXVec3Transform(&final_matrix, &pos3, &matrix); //Nhân ma trận transform

	return D3DXVECTOR3((float)final_matrix.x, (float)final_matrix.y, 0);
}


void CCamera::processInput()
{
	CResourcesManager *rs = CResourcesManager::GetInstance();

	if (rs->m_input->KeyDown(DIK_RIGHTARROW))
	{
		view_port.x += 2;
	}
	else if (rs->m_input->KeyDown(DIK_LEFTARROW))
	{
		view_port.x -= 2;
	}
	else if (rs->m_input->onKeyDown(DIK_UPARROW))
	{
		view_port.x += 0;
	}
}

D3DXVECTOR3 CCamera::Transform(D3DXVECTOR3 pos)
{
	return Transform(pos.x, pos.y);
}
