#ifndef _CBACKGROUND_H_
#define _CBACKGROUND_H_

#include "CTexture.h"
#include "Global.h"
#include "CResourcesManager.h"
#include <string>
#include <fstream>

using namespace std;
class CBackground
{
private:
	LPCWSTR _name;
	CTexture** _list_texture;//đóng vai trò dữ liệu
	CTexture** _map_texture; //đóng vai trò vẽ
	D3DXVECTOR2* _list_post;
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
