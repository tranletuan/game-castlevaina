#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "camera.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Background
{
protected:
	LPCWSTR file_name;
	D3DXVECTOR2 position;
	Texture **texture_map;
	Texture **texture_list;
	D3DXVECTOR2 *texture_pos;
	int total_texture;
	int width;
	int height;
	int texture_size;
	void LoadMap();

public:
	Background(LPCWSTR file_name, int texture_size);
	~Background();
	void LoadResources();
	void Draw(Camera camera);
	
};
#endif // !_BACKGROUND_H_
