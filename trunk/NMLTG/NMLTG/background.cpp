#include "background.h"

Background::Background(LPCWSTR file_name,int texture_size)
{
	this->file_name = LPCWSTR(file_name);
	this->texture_size = texture_size;
}

Background::~Background()
{
	for (int i = 0; i < height * width; i++)
	{
		delete[] texture_pos[i];
	}
	delete texture_pos;

	for (int i = 0; i < total_texture; i++)
	{
		delete[] texture_list[i];
	}
	delete texture_list;

}

void Background::LoadResources()
{
	wstring folder_background_map(kFolderBackground); //Thư mục chứ toàn bộ background
	wstring file_name(file_name); //Tên của background
	wstring folder_name(L"Map " + file_name + L"\\"); //Tên thư mục chưa background
	wstring full_folder_path(folder_background_map + folder_name); //Đường dẫn full đến background

	wstring file_map(full_folder_path + L"map_" + file_name + L".txt");
	wstring folder_texture(full_folder_path + L"texture_" + file_name + L"\\");

	ifstream infile(file_map);
	infile >> width >> height >> total_texture;

	//Load toàn bộ texture của map
	texture_list = new Texture*[total_texture];

	for (int i = 0; i < total_texture; i++)
	{
		wstring file_texture(folder_texture + to_wstring(i) + L".png");
		texture_list[i] = new Texture(file_texture.c_str());
	}

	int x = 0, y = texture_size * height; //Tọa độ lần lượt của texture
	texture_map = new Texture*[width * height];
	texture_pos = new D3DXVECTOR2[width * height];

	for (int i = 0; i < height; i++)
	{
		x = 0;
		for (int j = 0; j < width; j++)
		{
			int type = 0;
			infile >> type;
			texture_map[i * width + j] = texture_list[type];
			texture_pos[i * width + j] = D3DXVECTOR2(x, y);
			x += texture_size;
		}

		y -= texture_size;
	}
}

void Background::Draw(Camera camera)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			D3DXVECTOR2 pos = texture_pos[i * width + j];
			D3DXVECTOR3 pos_transform = camera.Transform(pos.x, pos.y);

			texture_map[i * width + j]->Draw(pos_transform.x, pos_transform.y);
		}
	}
}