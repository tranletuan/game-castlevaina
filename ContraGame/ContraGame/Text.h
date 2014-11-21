#ifndef CTEXT_H
#define CTEXT_H

#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <string>
using namespace std;

class CText
{

private:
	LPD3DXFONT m_font;
	char *m_fontName;
	LPD3DXSPRITE m_sprite;
	LPDIRECT3DDEVICE9 m_pd3D;
	int m_height;
	int m_width;


public:
	CText(LPD3DXFONT font, char *str, LPDIRECT3DDEVICE9 pd3d, LPD3DXSPRITE m_pSprite);
	~CText();

	bool init();
	void draw(string str);
	void draw(string str,D3DCOLOR color);
	void draw();

	void setHeight(int x){ m_height = x; }
	int getHeigth(){ return m_height; }
	void setWidth(int x){ m_width = x; }
	int getWidth(){ return m_width; }

	LPD3DXFONT getFont(){ return m_font; }


};


#endif