#include "Register.h"

CRegister::CRegister()
{

};

CRegister::CRegister(HINSTANCE hInstance)
{
	this->m_Hinst = hInstance;
}


bool CRegister::initWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style = CS_HREDRAW | CS_VREDRAW; 
	wcex.lpfnWndProc = (WNDPROC)WndProc; 
	wcex.cbClsExtra = 0; 
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 
	wcex.hIcon = 0; 
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 
	wcex.lpszMenuName  = NULL; 
	wcex.lpszClassName = NameClass; 
	wcex.hIconSm = 0;
	RegisterClassEx(&wcex);
	m_Hwnd = CreateWindow(
		NameClass,
		NameClass, 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		SCREEN_WIDTH, 
		SCREEN_HEIGTH, 
		NULL, 
		NULL, 
		hInstance, 
		NULL); 
	if (!m_Hwnd)
		return false;

	if (!SetWindowPos(m_Hwnd, HWND_NOTOPMOST, 200, 100, SCREEN_WIDTH, SCREEN_HEIGTH, SWP_SHOWWINDOW))
	{
		return false;
	}
	
	ShowWindow(m_Hwnd, SW_SHOW);
	UpdateWindow(m_Hwnd);
	return true;
}

HINSTANCE CRegister::gethInstance()
{
	return this->m_Hinst;
}

HWND CRegister::getHandle()
{
	return this->m_Hwnd;
}

LRESULT CALLBACK CRegister::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_DESTROY: 
		PostQuitMessage(0); 
		break;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}

CRegister::~CRegister()
{
}