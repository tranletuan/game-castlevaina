#include "Camera.h"

CCamera::CCamera()
{
	view_port.x = 0;
	view_port.y = kScreenHeight;
	_state = CamS_Follow;
	_vX = 2;

}

CCamera::CCamera(float posX, float posY)
{
	view_port.x = posX;
	view_port.y = posY;
	_state = CamS_Follow;
	_vX = 0.08;
	_vY = 0.08;
	_distanceX = kScreenWidth / 2;
	
}

void CCamera::UpdateCameraX(float x)
{
	if ((int)x > view_port.x + kScreenWidth / 2)
	{
		view_port.x = (int)x - kScreenWidth / 2;
	}
}

void CCamera::UpdateCameraY(float y)
{
	if ((int)y > view_port.y - kScreenHeight / 2)
	{
		view_port.y = (int)y + kScreenHeight / 2;
	}
}

void CCamera::Update(int time)
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	switch (_state)
	{
	case CamS_Move:
		if (rs->m_curMap == 2)
		{
			MoveY(time);
		}
		else
		{
			MoveX(time);
		}
		break;
	case CamS_Follow:
		if (rs->m_curMap == 2)
		{
			if (rs->m_posBill.y < rs->m_heightMap - 216)
			{
				UpdateCameraY(rs->m_posBill.y);
			}
			else
			{
				_state = CamS_Move;
			}
		}		
		else 
		{
			if (rs->m_posBill.x < rs->m_widthMap - kScreenWidth)
			{
				UpdateCameraX(rs->m_posBill.x);
			}
			else
			{
				_state = CamS_Move;
			}
		}
		break;
	case CamS_Stop:
		if (rs->m_curMap == 2)
		{
			if (rs->m_heightMap - kScreenHeight < view_port.y)
			{
				view_port.y = rs->m_heightMap - kScreenHeight;
			}
		}		
		else
		{
			if (rs->m_widthMap - kScreenWidth < view_port.x)
			{
				view_port.x = rs->m_widthMap - kScreenWidth;
			}
		}
		break;
	default:
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
	if (rs->m_input->KeyDown(DIK_LEFTARROW))
	{
		view_port.x -= 2;
	}
	if (rs->m_input->KeyDown(DIK_UP))
	{
		view_port.y += 10;
	}
	if (rs->m_input->KeyDown(DIK_DOWN))
	{
		view_port.y -= 10;
	}
}

D3DXVECTOR3 CCamera::Transform(D3DXVECTOR3 pos)
{
	return Transform(pos.x, pos.y);
}

void CCamera::MoveX(int time)
{
	int delta = (int)time*_vX;
	view_port.x += delta;
	if (_distanceX <= 0)
	{
		_state = CamS_Stop;
		_distanceX = kScreenWidth / 2;
	}
	else
	{
		_distanceX -= delta;
	}
}

void CCamera::MoveY(int time)
{
	int delta = (int)time*_vY;
	view_port.y += delta;
	if (view_port.y >= CResourcesManager::GetInstance()->m_heightMap)
	{
		_state = CamS_Stop;		
	}
	
}