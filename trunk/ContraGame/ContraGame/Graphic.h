#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <d3d9.h>
#include <d3dx9.h>



class CGraphic
{
private:
	LPDIRECT3D9 m_pd3d;
	LPDIRECT3DDEVICE9 m_pd3Device;	
	IDirect3DSurface9* m_backbuffer;

public:
	CGraphic();
	~CGraphic();

	bool initDevice(HWND _hWnd);
	LPDIRECT3D9 getPd3d();
	LPDIRECT3DDEVICE9 getPd3Device();
	IDirect3DSurface9* getBackbuffer();

	void releaseDevice();
	void beginRender();
	void endRender();

};

#endif