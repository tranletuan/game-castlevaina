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
extern bool			G_IsInitedDX;		//Kiểm tra khởi tạo DirectX
extern int			G_GameDepth;		//Chỉ số độ sâu
extern LPWSTR		G_GameName;			//Tên cửa sổ game
extern int			G_FrameRate;		//Tỷ lệ chuyển chuyển frame (30->60)
extern int			G_ColorMode;
extern bool			G_IsFullScreen;		//Toàn màn hình
extern D3DFORMAT	G_BackBufferFormat;

extern int			G_ScreenWidth;		//Chiều ngang màn hình
extern int			G_ScreenHeight;		//Chiều cao màn hình
extern RECT			G_WindowSize;		//Khung màn hình

extern HINSTANCE					G_hInstance;	//Yêu cầu từ màn hình game
extern HWND							G_hWnd;			//Xử lý cửa sổ

extern LPDIRECT3D9					G_DirectX;		//Đối tượng directX
extern LPDIRECT3DDEVICE9			G_Device;		//Thiết bị
extern LPDIRECT3DSURFACE9			G_BackBuffer;	//Vùng đệm	

extern LPDIRECTINPUT8				G_DirectInput;	//Đối tượng đầu vào	
extern LPDIRECTINPUTDEVICE8			G_KeyBoard;		//Bàn phím	
extern LPD3DXSPRITE					G_SpriteHandler;//Đối tượng vẽ texture	


void GLMessage(LPWSTR text);

#endif