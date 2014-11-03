#include "CBackground.h"

CBackground::CBackground(LPCWSTR _name, int texture_size)
{
	this->_name = _name;
	this->_texture_size = texture_size;
}

CBackground::~CBackground()
{
	if (_background_sprite != NULL) delete _background_sprite;
	if (_background_texture != NULL) delete _background_texture;
	if (_background_map.size() > 0) _background_map.clear();
}

void CBackground::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	CCamera* c = rs->_camera;

	wstring folder_background(MAP_FOLDER); //Thư mục chứa toàn bộ background
	wstring background_name(_name);
	wstring full_folder_path(folder_background + background_name + L"/"); //Đường dẫn full đến background

	wstring file_map_txt(full_folder_path + L"background_map_" + background_name + L".txt");
	wstring file_texture(full_folder_path + L"background_texture_" + background_name + L".png");

	ifstream infile(file_map_txt);
	infile >> this->_num_col;
	infile >> this->_num_row;
	infile >> this->_total;

	//Load toàn bộ texture của map
	_background_texture = new CTexture(file_texture.c_str(), _total);
	_background_sprite = new CSprite(_background_texture);
	
	int x = 0;
	int y = kScreenHeight;
	for (int i = 0; i < _num_row; i++)
	{
		x = 0;
		for (int j = 0; j < _num_col; j++)
		{
			int type = 0;
			infile >> type; //đọc type texture 
			D3DXVECTOR3 pos = D3DXVECTOR3(x, y - _texture_size / 2, 0);
			_background_map[pos] = type;
			x += _texture_size;
		}

		y -= _texture_size;
	}
}

void CBackground::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;

	if (_background_map.size() > 0)
	{
		for (map<D3DXVECTOR3, int>::iterator i = _background_map.begin(); i != _background_map.end(); i++)
		{
			int index = (*i).second;
			D3DXVECTOR3 pos_ = (*i).first;
			D3DXVECTOR3 pos = c->Transform((*i).first);
			_background_sprite->SelectFrameOf((*i).second);
			_background_sprite->Draw(pos.x, pos.y);
		}
	}
}