#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>

//CONSTANT

//view mode 24bit
#define GL_RESOLUTION_640_480_24	0
#define GL_RESOLUTION_800_600_24	1
#define GL_RESOLUTION_1024_768_24	2
//view mode 32bit
#define GL_RESOLUTION_640_480_32	10
#define GL_RESOLUTION_800_600_32	11
#define GL_RESOLUTION_1024_768_32	12

#define GL_KEY_BUFFER_SIZE	1024

//---//
//
extern LPWSTR		kGameName;			//Tên cửa sổ game
extern int			kFrameRate;		//Tỷ lệ chuyển chuyển frame (30->60)
extern bool			kIsFullScreen;		//Toàn màn hình
extern D3DFORMAT	kBackBufferFormat;

extern int			kScreenWidth;		//Chiều ngang màn hình
extern int			kScreenHeight;		//Chiều cao màn hình
extern RECT			kWindowSize;		//Khung màn hình

extern HINSTANCE					kHInstance;	//Yêu cầu từ màn hình game
extern HWND							kHWND;			//Xử lý cửa sổ

extern LPDIRECT3D9					kDirectX;		//Đối tượng directX
extern LPDIRECT3DDEVICE9			kDevice;		//Thiết bị
extern LPDIRECT3DSURFACE9			kBackBuffer;	//Vùng đệm	

extern LPDIRECTINPUT8				kDirectInput;	//Đối tượng đầu vào	
extern LPDIRECTINPUTDEVICE8			kKeyBoard;		//Bàn phím	
extern LPD3DXSPRITE					kSpriteHandler;//Đối tượng vẽ texture	
extern LPD3DXFONT					kFont;

//GAME CONSTANT
extern float						kZoom;
extern D3DCOLOR						kBackgroundColorTexture;
#endif