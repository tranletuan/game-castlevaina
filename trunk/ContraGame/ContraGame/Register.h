#ifndef REGISTER_H
#define REGISTER_H

#include <d3d9.h>
#include <d3dx9.h>

#define NameClass "Contra Game"
#define SCREEN_WIDTH 256
#define SCREEN_HEIGTH 240

class CRegister
{
private:
	HINSTANCE m_Hinst;		
	HWND m_Hwnd;			
public:
	CRegister(HINSTANCE hInstance);
	CRegister();
	~CRegister();

	bool initWindow(HINSTANCE hInstance);
	HINSTANCE gethInstance();
	HWND getHandle();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

#endif