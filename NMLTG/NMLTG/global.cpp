#include "Global.h"

//CONSTANT
LPWSTR		kGameName = L"Contra";	//Tên cửa sổ game
int			kFrameRate = 60;		//Tỷ lệ chuyển chuyển frame (30->60)
bool		kIsFullScreen = false;	//Toàn màn hình
D3DFORMAT	kBackBufferFormat = D3DFMT_X8R8G8B8;

int			kScreenWidth = 256;		//Chiều ngang màn hình
int			kScreenHeight = 256;	//Chiều cao màn hình
RECT		kWindowSize;

HINSTANCE					kHInstance;	//Yêu cầu từ màn hình game
HWND						kHWND;
LPDIRECT3D9					kDirectX;
LPDIRECT3DDEVICE9			kDevice;
LPDIRECT3DSURFACE9			kBackBuffer;

LPDIRECTINPUT8				kDirectInput;
LPDIRECTINPUTDEVICE8		kKeyBoard;
LPD3DXSPRITE				kSpriteHandler;
LPD3DXFONT					kFont = 0;

//GAME CONSTANT
float						kZoom = 2;
D3DCOLOR					kBackgroundColorTexture = D3DCOLOR_XRGB(255, 0, 255); //Thiết lập chỉ số để xóa nền texture
LPCWSTR						kBackgroundFolder = L"resources/map/";

