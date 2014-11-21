#include <d3dx9.h>
#include "Utils.h"

//LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, string FilePath)
//{
//	std::wstring stemp = s2ws(FilePath);
//	LPCWSTR result = stemp.c_str();
//
//	D3DXIMAGE_INFO info;
//
//	HRESULT result = D3DXGetImageInfoFromFileW(result, &info);
//	if (result != D3D_OK)
//	{
//		GLMessage("Can't load surface");
//		return NULL;
//	}
//
//	LPDIRECT3DSURFACE9 surface;
//
//	d3ddv->CreateOffscreenPlainSurface(
//		info.Width,				// width
//		info.Height,			// height
//		D3DFMT_X8R8G8B8,		// format
//		D3DPOOL_DEFAULT,
//		&surface,
//		NULL);
//
//	//result = D3DXLoadSurfaceFromFile(
//	//	surface, 		// surface
//	//	NULL,			// destination palette	
//	//	NULL,			// destination rectangle 
//	//	FilePath.c_str(),
//	//	NULL,			// source rectangle
//	//	D3DX_DEFAULT, 	// filter image
//	//	D3DCOLOR_XRGB(0, 0, 0),				// transparency (0 = none)
//	//	NULL);			// reserved
//
//	if (result != D3D_OK)
//	{
//		GLMessage("[ERROR] D3DXLoadSurfaceFromFile() failed");
//		return NULL;
//	}
//
//	return surface;
//}

void DisplayText(string text)
{
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	RECT rct;
	rct.left = 2;
	rct.right = kScreenWidth;
	rct.top = 10;
	rct.bottom = rct.top + 20;

	// Draw some text
	kFont->DrawText(NULL, text.c_str(), -1, &rct, 0, fontColor);
}

void GLMessage(string text)
{
	MessageBox(kHWND, text.c_str(), "Voice", MB_OK);
}

wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
};