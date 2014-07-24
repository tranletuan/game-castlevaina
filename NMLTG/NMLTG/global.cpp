#include "global.h"

//CONSTANT
bool		kIsInitedDX = false;		//Kiểm tra khởi tạo DirectX
int			kGameDepth = 24;		//Chỉ số độ sâu
LPWSTR		kGameName = L"Castlevania";			//Tên cửa sổ game
int			kFrameRate = 60;		//Tỷ lệ chuyển chuyển frame (30->60)
int			kColorMode;
bool		kIsFullScreen = false;		//Toàn màn hình
D3DFORMAT	kBackBufferFormat = D3DFMT_X8R8G8B8;

int			kScreenWidth = 256;		//Chiều ngang màn hình
int			kScreenHeight = 176;		//Chiều cao màn hình
RECT		kWindowSize;

HINSTANCE					kHInstance;	//Yêu cầu từ màn hình game
HWND						kHWND;
LPDIRECT3D9					kDirectX;
LPDIRECT3DDEVICE9			kDevice;
LPDIRECT3DSURFACE9			kBackBuffer;

LPDIRECTINPUT8				kDirectInput;
LPDIRECTINPUTDEVICE8		kKeyBoard;
LPD3DXSPRITE				kSpriteHandler;

//GAME CONSTANT
LPCWSTR						kFolderBackground = L"H:\\Users\\Tran\\Desktop\\Map 1\\";

void GLMessage(LPWSTR text)
{
	MessageBox(kHWND, text, L"Castlevania Voice", MB_OK);
}