#pragma once
#ifndef _CSURFACE_H
#define _CSURFACE_H

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

using namespace std;

class CSurface
{
private:
	LPDIRECT3DDEVICE9					m_pd3dDevice;
	LPDIRECT3DSURFACE9					m_image;
	D3DXIMAGE_INFO						m_info;
	int									m_width;			// width of image
	int									m_height;		// height of image
public:
	CSurface(LPDIRECT3DDEVICE9 pd3dDevice);
	~CSurface();

	// Load texture from file
	bool loadSurface(string filename, D3DCOLOR transcolor);
	bool loadSurface(string filename);
	
	void draw(RECT srcRect, RECT destRect, IDirect3DSurface9* surface);
	void draw(IDirect3DSurface9* surface);

	LPDIRECT3DSURFACE9 getImage() { return m_image; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	D3DXIMAGE_INFO getInfo() { return m_info; }


};
#endif

