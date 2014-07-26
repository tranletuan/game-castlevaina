#include "texture.h"
#include "global.h"

Texture::Texture()
{
	file_name = NULL;
	size = RECT();
	num_cols = 0;
	num_rows = 0;
	count = 0;
	frame_width = 0;
	frame_height = 0;
	picture = NULL;
}

Texture::Texture(const Texture &texture)
{
	file_name = LPCWSTR(texture.file_name);
	size = texture.size;
	num_cols = texture.num_cols;
	num_rows = texture.num_rows;
	count = texture.count;
	frame_width = texture.frame_width;
	frame_height = texture.frame_height;
	picture = texture.picture;
}

Texture::Texture(LPCWSTR file_name, int num_cols, int num_rows, int count)
{
	this->file_name = LPCWSTR(file_name);
	this->num_cols = num_cols;
	this->num_rows = num_rows;
	this->count = count;
	Load();
}

Texture::~Texture()
{
	if (this->picture != NULL)
	{
		this->picture->Release();
	}
}

void Texture::Draw(int x, int y)
{
	D3DXVECTOR3 pos((float)x, (float)y, 0);
	kSpriteHandler->Draw(picture, &size, NULL, &pos, 0xFFFFFFFF);
}

void Texture::Load()
{
	D3DXIMAGE_INFO info;
	HRESULT hrs;

	//Đọc thông tin file
	hrs = D3DXGetImageInfoFromFile(file_name, &info);
	RECT s = { 0, 0, info.Width, info.Height };
	size = s;

	frame_width = info.Width / num_cols;
	frame_height = info.Height / num_rows;
	width = info.Width;
	height = info.Height;

	//Load hình ảnh
	hrs = D3DXCreateTextureFromFileEx(
		kDevice,
		file_name,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		kBackgroundColorTexture,
		&info,
		NULL,
		&picture);

	if (hrs != D3D_OK)
	{
		GLMessage(L"Can not load texture");
		return;
	}
}