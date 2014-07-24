#include "camera.h"

Camera::Camera()
{
	view_port.x = 0;
	view_port.y = kScreenHeight;
}

void Camera::UpdateCamera(int x)
{
	view_port.x = x - kScreenWidth / 2;
	if (view_port.x < 0)
	{
		view_port.x = 0;
	}

}

D3DXVECTOR3 Camera::Transform(int x, int y)
{
	//Ma trận view port
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -view_port.x;
	matrix._42 = view_port.y;

	//Tọa độ hiện tại
	D3DXVECTOR3 pos3(x, y, 1);
	D3DXVECTOR4 final_matrix;
	D3DXVec3Transform(&final_matrix, &pos3, &matrix); //Nhân ma trận transform

	return D3DXVECTOR3((float)final_matrix.x, (float)final_matrix.y, 0);
}
