#ifndef _GAME_H_
#define _GAME_H_

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <string>
#include "Global.h"
#include "Utils.h"

using namespace std;

class CGame
{
public:
	CGame(int cmd_show);
	~CGame();
	void GameInit();
	void GameRun();
	void GameEnd();

protected:
	int cmd_show;
	DWORD delta_time; //Thời gian chuyển frame
	BYTE key_states[256];
	DIDEVICEOBJECTDATA key_events[GL_KEY_BUFFER_SIZE];

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool InitWindow(); //Khởi tạo cửa sổ
	bool InitDirectX(); //Khởi tạo đối tượng directx
	bool InitInput(); //Khởi tạo bàn phím
	void ProcessKeyboard(); //Nhận sự kiện 
	void RenderAll(); //Vẽ hình lên của sổ
	int IsKeyDown(int key_code);

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3d_device); //Vẽ các thành phần trong game
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3d_device);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3d_device, int delta); //Xử lý phím
	virtual void OnKeyDown(int key_code);
	virtual void OnKeyUp(int key_code);
	virtual void GameUpdate(int delta_time);

	LPDIRECT3DSURFACE9 _background;
};
#endif // ! _GAME_H_
