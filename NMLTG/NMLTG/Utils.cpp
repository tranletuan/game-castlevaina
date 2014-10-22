#include <d3dx9.h>

#include "Utils.h"


LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath)
{
	D3DXIMAGE_INFO info;

	HRESULT result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		GLMessage(L"Can't load surface");
		return NULL;
	}

	LPDIRECT3DSURFACE9 surface;

	d3ddv->CreateOffscreenPlainSurface(
		info.Width,				// width
		info.Height,			// height
		D3DFMT_X8R8G8B8,		// format
		D3DPOOL_DEFAULT,
		&surface,
		NULL);

	result = D3DXLoadSurfaceFromFile(
		surface, 		// surface
		NULL,			// destination palette	
		NULL,			// destination rectangle 
		FilePath,
		NULL,			// source rectangle
		D3DX_DEFAULT, 	// filter image
		D3DCOLOR_XRGB(0, 0, 0),				// transparency (0 = none)
		NULL);			// reserved

	if (result != D3D_OK)
	{
		GLMessage(L"[ERROR] D3DXLoadSurfaceFromFile() failed");
		return NULL;
	}

	return surface;
}

void DisplayText(string text)
{
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	RECT rct;
	rct.left = 2;
	rct.right = kScreenWidth;
	rct.top = 10;
	rct.bottom = rct.top + 20;

	string From = text;
	wstring To(From.begin(), From.end());
	LPCWSTR Last = To.c_str();

	// Draw some text
	kFont->DrawText(NULL, Last, -1, &rct, 0, fontColor);
}

void GLMessage(LPCWSTR text)
{
	MessageBox(kHWND, text, L"Voice", MB_OK);
}

void GLMessage(string text)
{
	string From = text;
	wstring To(From.begin(), From.end());
	LPCWSTR Last = To.c_str();

	MessageBox(kHWND, Last, L"Voice", MB_OK);
}