#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"
#include "Utils.h"
#include <string>
#include <stdio.h>

using namespace std;

class CTexture
{
public:
	string file_name;
	RECT size;
	LPDIRECT3DTEXTURE9 picture;
	int num_cols;
	int num_rows;
	int count; // total tile
	int frame_width;  // width tile
	int frame_height; // height tile
	int width; // width image
	int height; // height mage
	D3DCOLOR _color;	

	CTexture();
	CTexture(const CTexture &texture);
	CTexture(string file_name, int num_cols = 1, int num_rows = 1);
	CTexture(string file_name, D3DCOLOR color, int num_cols = 1, int num_rows = 1);
	~CTexture();

	
	void Draw(int x, int y);

protected:
	void Load();
	void Load(D3DCOLOR color);
};
#endif // !_TEXTURE_H_
