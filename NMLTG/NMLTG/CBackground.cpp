#include "CBackground.h"

CBackground::CBackground(LPCWSTR _name, int texture_size)
{
	this->_name = _name;
	this->_texture_size = texture_size;
}

CBackground::~CBackground()
{
}

void CBackground::LoadResources()
{
	wstring folder_background(kBackgroundFolder); //Thư mục chứ toàn bộ background
	wstring background_name(_name);
	wstring full_folder_path(folder_background + background_name + L"/"); //Đường dẫn full đến background

	wstring file_map_txt(full_folder_path + L"map_" + background_name + L".txt");
	wstring folder_texture(full_folder_path + L"texture_" + background_name + L"/");

	ifstream infile(file_map_txt);
	infile >> this->_num_col;
	infile >> this->_num_row;
	infile >> this->_total;

	//Load toàn bộ texture của map
	_list_texture = new CTexture*[_total];

	for (int i = 0; i < _total; i++)
	{
		wstring file_texture(folder_texture + to_wstring(i) + L".png");
		_list_texture[i] = new CTexture(file_texture.c_str());
	}

	int x = 0, y = kScreenHeight; //Tọa độ lần lượt của texture
	_map_texture = new CTexture*[_num_col * _num_row];
	_list_post = new D3DXVECTOR2[_num_col * _num_row];

	for (int i = 0; i < _num_row; i++)
	{
		x = 0;
		for (int j = 0; j < _num_col; j++)
		{
			int type = 0;
			infile >> type; //đọc type texture 
			_map_texture[i * _num_col + j] = _list_texture[type];
			_list_post[i * _num_col + j] = D3DXVECTOR2(x, y);
			x += _texture_size;
		}

		y -= _texture_size;
	}
}

void CBackground::Draw()
{
	CCamera* camera = CResourcesManager::GetInstance()->_camera;

	for (int i = 0; i < _num_row; i++)
	{
		for (int j = 0; j < _num_col; j++)
		{
			D3DXVECTOR2 pos = _list_post[i * _num_col + j];
			D3DXVECTOR3 pos_transform = camera->Transform(pos.x, pos.y);

			_map_texture[i * _num_col + j]->Draw(pos_transform.x, pos_transform.y);
		}
	}
}