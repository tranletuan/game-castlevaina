#include "Global.h"

//CONSTANT
bool		G_IsInitedDX = false;		//Kiểm tra khởi tạo DirectX
int			G_GameDepth;		//Chỉ số độ sâu
LPWSTR		G_GameName = L"Castlevania";			//Tên cửa sổ game
int			G_FrameRate = 60;		//Tỷ lệ chuyển chuyển frame (30->60)
int			G_ColorMode;
bool		G_IsFullScreen = false;		//Toàn màn hình
D3DFORMAT	G_BackBufferFormat;

int			G_ScreenWidth = 640;		//Chiều ngang màn hình
int			G_ScreenHeight = 480;		//Chiều cao màn hình
RECT		G_WindowSize;

HINSTANCE					G_hInstance;	//Yêu cầu từ màn hình game
HWND						G_hWnd;
LPDIRECT3D9					G_DirectX;
LPDIRECT3DDEVICE9			G_Device;
LPDIRECT3DSURFACE9			G_BackBuffer;

LPDIRECTINPUT8				G_DirectInput;
LPDIRECTINPUTDEVICE8		G_KeyBoard;
LPD3DXSPRITE				G_SpriteHandler;



void GLMessage(LPWSTR text)
{
	MessageBox(G_hWnd, text, L"Castlevania Voice", MB_OK);
}