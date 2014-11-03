#ifndef _CBACKGROUND_H_
#define _CBACKGROUND_H_

#include "CResourcesManager.h"
#include "Config.h"
#include <string>
#include <fstream>
#include <map>

using namespace std;
class CBackground
{
private:
	LPCWSTR _map_name;
	CTexture* _background_texture;
	CSprite* _background_sprite;
	map<D3DXVECTOR3, int> _background_map;

	int _num_col;
	int _num_row;
	int _total;
	int _texture_size;


public:
	CBackground(LPCWSTR _name, int texture_size);
	~CBackground();
	void LoadResources();
	void Draw();
};
#endif // !_CBACKGROUND_H_
