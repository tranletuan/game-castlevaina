#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <d3d9.h>
#include <d3dx9.h>

class Texture
{
public:
	LPWSTR file_name;
	RECT size;
	LPDIRECT3DTEXTURE9 picture;
	int num_cols;
	int num_rows;
	int count;
	int frame_width;
	int frame_height;

	Texture(const Texture &texture);
	Texture(LPWSTR file_name, int num_cols = 1, int num_rows = 1, int count = 1);
	~Texture();
	void Draw(int x, int y);

protected:
	void Load();
};
#endif // !_TEXTURE_H_
