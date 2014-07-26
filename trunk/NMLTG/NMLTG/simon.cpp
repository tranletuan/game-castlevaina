#include "simon.h"

Simon::Simon(D3DXVECTOR2 pos)
{
	this->pos = pos;
	sprite_normal = NULL;
}

Simon::~Simon()
{
	/*if (sprite_normal != NULL)
		delete sprite_normal;*/
}
void Simon::LoadResources()
{
	texture = new Texture(L"H:\\Users\\Tran\\Desktop\\normal.png", 9, 1, 9);
	sprite_normal = new Sprite(texture, 300);
}

void Simon::Update(int delta)
{
	//Cập nhật các trạng thái của simon

	//Tọa độ
	pos.x += vx * delta;
	pos.y += vy * delta;

	//
}

void Simon::Draw(Camera camera)
{
	D3DXVECTOR3 pos_transfer = camera.Transform(pos.x, pos.y);
	sprite_normal->SelectFrameOf(10);
	sprite_normal->Draw(pos_transfer.x, pos_transfer.y);
}

