#include "Text.h"

CText::CText(LPD3DXFONT font, char *fontName, LPDIRECT3DDEVICE9 pd3d, LPD3DXSPRITE m_pSprite)
{
	m_font = font;
	m_fontName = fontName;
	m_pd3D = pd3d;
	m_sprite = m_pSprite;
}

bool CText::init()
{
	if (m_font)
	{
		m_font->Release();
	}

	// font description struct
	D3DXFONT_DESC	m_fontDesc;

	ZeroMemory(&m_fontDesc, sizeof(D3DXFONT_DESC));
	m_fontDesc.Height = 20;
	m_fontDesc.Width = 30;
	m_fontDesc.Weight = 20;
	m_fontDesc.MipLevels = D3DX_DEFAULT;
	m_fontDesc.Italic = false;
	m_fontDesc.CharSet = 0;
	m_fontDesc.OutputPrecision = 0;
	m_fontDesc.Quality = 0;
	m_fontDesc.PitchAndFamily = 0;
	strcpy_s(m_fontDesc.FaceName, m_fontName); // name will be something like "Arial"


	if (FAILED(D3DXCreateFontIndirect(m_pd3D, &m_fontDesc, &m_font)))
		return false;

	

	return true;
}

void CText::draw(string str)
{

	RECT rect;

	rect.left = 0;
	rect.top = 0;
	rect.right = 256;
	rect.bottom = 240;
	string a = "asd";

	m_font->DrawText(m_sprite, // <-- the sprite
		str.c_str(),  // <-- the text
		-1, // <-- num characters in string  -1 means its null terminated
		&rect, // <--- position <limits>
		DT_TOP | DT_LEFT, // <--- alignment in the rect
		D3DCOLOR_XRGB(0, 0, 0)); // Color   
}

void CText::draw(string str,D3DCOLOR color)
{
	RECT rect;

	rect.left = 0;
	rect.top = 0;
	rect.right = 256;
	rect.bottom = 240;

	string a = "asd";

	m_font->DrawText(m_sprite, // <-- the sprite
		str.c_str(),  // <-- the text
		-1, // <-- num characters in string  -1 means its null terminated
		&rect, // <--- position <limits>
		DT_TOP | DT_LEFT, // <--- alignment in the rect
		D3DCOLOR_XRGB(0, 0, 255)); // Color   
}
void CText::draw()
{
	RECT rect;

	rect.left = 0;
	rect.top = 0;
	rect.right = 256;
	rect.bottom = 240;
	string a = "asd";

	m_font->DrawText(m_sprite, // <-- the sprite
		a.c_str(),  // <-- the text
		-1, // <-- num characters in string  -1 means its null terminated
		&rect, // <--- position <limits>
		DT_TOP | DT_LEFT, // <--- alignment in the rect
		D3DCOLOR_XRGB(0, 0, 0)); // Color   
}



CText::~CText()
{

}