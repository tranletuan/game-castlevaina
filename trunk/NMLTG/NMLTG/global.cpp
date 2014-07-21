#include "global.h"

//CONSTANT
bool		kIsInitedDX = false;		//Kiểm tra khởi tạo DirectX
int			kGameDepth;		//Chỉ số độ sâu
LPWSTR		kGameName = L"Castlevania";			//Tên cửa sổ game
int			kFrameRate = 60;		//Tỷ lệ chuyển chuyển frame (30->60)
int			kColorMode;
bool		kIsFullScreen = false;		//Toàn màn hình
D3DFORMAT	kBackBufferFormat;

int			kScreenWidth = 640;		//Chiều ngang màn hình
int			kScreenHeight = 480;		//Chiều cao màn hình
RECT		kWindowSize;

HINSTANCE					kHInstance;	//Yêu cầu từ màn hình game
HWND						kHWND;
LPDIRECT3D9					kDirectX;
LPDIRECT3DDEVICE9			kDevice;
LPDIRECT3DSURFACE9			kBackBuffer;

LPDIRECTINPUT8				kDirectInput;
LPDIRECTINPUTDEVICE8		kKeyBoard;
LPD3DXSPRITE				kSpriteHandler;



void GLMessage(LPWSTR text)
{
	MessageBox(kHWND, text, L"Castlevania Voice", MB_OK);
}