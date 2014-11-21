#include "Graphic.h"

CGraphic::CGraphic()
{
	m_pd3d = NULL;
	m_pd3Device = NULL;

}

bool CGraphic::initDevice(HWND hWnd)
{
	// Create the DirectX object
	if (NULL == (m_pd3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}
	// Fill the presentation parameters structure
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = 240;
	d3dpp.BackBufferWidth = 256;
	d3dpp.hDeviceWindow = hWnd;
	// Create a default DirectX device
	if (FAILED(m_pd3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_REF,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pd3Device)))
	{
		return false;
	}
	return true;
}



void CGraphic::beginRender()
{
	if (m_pd3Device != NULL)
	{
		m_pd3Device->BeginScene();
		// Clear the backbuffer to a blue color
		m_pd3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	}
}

IDirect3DSurface9* CGraphic::getBackbuffer()
{
	IDirect3DSurface9* backbuffer = NULL;

	if (!m_pd3Device)
		return NULL;

	HRESULT hResult = m_pd3Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backbuffer);
	if (FAILED(hResult))
		return NULL;
	else
		return m_backbuffer;
}

void CGraphic::endRender()
{
	m_pd3Device->EndScene();
	m_pd3Device->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3D9 CGraphic::getPd3d()
{
	return this->m_pd3d;
}

LPDIRECT3DDEVICE9 CGraphic::getPd3Device()
{
	return this->m_pd3Device;
}

void CGraphic::releaseDevice()
{

	if (m_pd3d != NULL)
	{
		m_pd3d->Release();
		m_pd3d = NULL;
	}
	if (m_pd3Device != NULL)
	{
		m_pd3Device->Release();
		m_pd3Device = NULL;
	}
}

CGraphic::~CGraphic()
{

}