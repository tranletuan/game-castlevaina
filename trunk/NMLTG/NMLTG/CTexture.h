#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"
#include "Utils.h"

class CTexture
{
public:
	LPCWSTR file_name;
	RECT size;
	LPDIRECT3DTEXTURE9 picture;
	int num_cols;
	int num_rows;
	int count;
	int frame_width;
	int frame_height;
	int width;
	int height;

	CTexture();
	CTexture(const CTexture &texture);
	CTexture(LPCWSTR file_name, int num_cols = 1, int num_rows = 1);
	~CTexture();
	void Draw(int x, int y);

protected:
	void Load();
};
#endif // !_TEXTURE_H_
