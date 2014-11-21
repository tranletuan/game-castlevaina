#include "Surface.h"

CSurface::CSurface(LPDIRECT3DDEVICE9 pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;
}

CSurface::~CSurface()
{
	if (m_image != NULL) m_image->Release();
}

bool CSurface::loadSurface(string filename)
{
	return loadSurface(filename, D3DCOLOR_XRGB(255, 255, 255));
}

bool CSurface::loadSurface(string filename, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 surface = NULL;
	HRESULT result;

	// get width and height from file
	result = D3DXGetImageInfoFromFile(filename.c_str(), &m_info);

	if (result != D3D_OK)
		return NULL;

	// create surface
	result = m_pd3dDevice->CreateOffscreenPlainSurface(m_info.Width,
		m_info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_image,
		NULL);

	if (result != D3D_OK)
		return false;

	//load surface from file into newly created surface
	result = D3DXLoadSurfaceFromFile(m_image,
		NULL,
		NULL,
		filename.c_str(),
		NULL,
		D3DX_DEFAULT,
		transcolor,
		NULL);

	// make sure file was load okay
	if (result != D3D_OK)
		return false;

	if (m_image != NULL)
	{
		m_width = m_info.Width;
		m_height = m_info.Height;
	}
	else
	{
		m_width = m_height = -1;
	}

	return true;
}

void CSurface::draw(RECT srcRect, RECT destRect, IDirect3DSurface9* surface)
{
	m_pd3dDevice->StretchRect(getImage(),
		&srcRect,
		surface,
		&destRect,
		D3DTEXF_NONE);
}
void CSurface::draw(IDirect3DSurface9* surface)
{
	m_pd3dDevice->StretchRect(getImage(),
		NULL,
		surface,
		NULL,
		D3DTEXF_NONE);
}