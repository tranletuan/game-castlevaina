#ifndef _GAME_H_
#define _GAME_H_

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Global.h"

class CGame
{
public:
	CGame(int cmdShow);
	~CGame();
	void gameInit();
	void gameRun();
	void gameEnd();

protected:
	int cmdShow;
	static LRESULT CALLBACK winProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	DWORD deltaTime; //Thời gian chuyển frame
	BYTE keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[GL_KEY_BUFFER_SIZE];
	bool initWindow(int cmdShow); //Khởi tạo cửa sổ
	bool initDirectX(); //Khởi tạo đối tượng directx
	bool initInput(); //Khởi tạo bàn phím
	void processKeyboard(); //Nhận sự kiện 
	void renderAll(); //Vẽ hình lên của sổ
	int isKeyDown(int keyCode);

	virtual void renderFrame(LPDIRECT3DDEVICE9 d3dDevice, int delta); //Vẽ các thành phần trong game
	virtual void loadResources(LPDIRECT3DDEVICE9 d3dDevice);
	virtual void processInput(LPDIRECT3DDEVICE9 d3dDevice, int delta); //Xử lý phím
};
#endif // ! _GAME_H_
