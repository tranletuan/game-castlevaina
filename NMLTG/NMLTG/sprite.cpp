#include "sprite.h"
#include "global.h"

Sprite::Sprite()
{
	sprite_texture = NULL;
	start = 0;
	end = 0;
	index = 0;
	time_ani = 0;
	time_local = 0;
}

Sprite::Sprite(const Sprite &sprite)
{
	sprite_texture = sprite.sprite_texture;
	start = sprite.start;
	end = sprite.end;
	index = sprite.index;
	time_ani = sprite.time_ani;
	time_local = sprite.time_local;
}

Sprite::Sprite(Texture *texture, int start, int end, int time_ani) 
: sprite_texture(texture)
{
	this->start = start;
	this->end = end;
	this->index = start;
	this->time_ani = time_ani;
	this->time_local = 0;
}

Sprite::Sprite(Texture *texture, int time_ani) :sprite_texture(texture)
{
	this->start = 0;
	this->end = texture->count - 1;
	this->time_ani = time_ani;
	this->index = 0;
	this->time_local = 0;
}

void Sprite::Next()
{
	index++;
	if (index > end)
	{
		index = start;
	}
}

void Sprite::Reset()
{
	index = start;
	time_local = 0;
}

void Sprite::SelectFrameOf(int index)
{
	this->index = index;
}

void Sprite::UpdateEffect(int elapsed_time)
{
	time_local += elapsed_time;

	if (time_local >= time_ani)
	{
		time_local = 0;
		Next();
	}
}

void Sprite::Draw(int x, int y)
{
	RECT srcRect;

	srcRect.left = (index % sprite_texture->num_cols) * sprite_texture->frame_width;
	srcRect.top = (index / sprite_texture->num_rows) * sprite_texture->frame_height;
	srcRect.right = srcRect.left + sprite_texture->frame_width;
	srcRect.bottom = srcRect.top + sprite_texture->frame_height;

	D3DXVECTOR3 pos((float)x, (float)y, 0);

	kSpriteHandler->Draw(
		sprite_texture->picture,
		&srcRect,
		NULL,
		&pos,
		0xFFFFFFFF);
}

void Sprite::DrawFlipX(int x, int y)
{
	D3DXMATRIX oldMatrix;
	kSpriteHandler->GetTransform(&oldMatrix);

	D3DXMATRIX newMatrix;
	D3DXVECTOR2 center = D3DXVECTOR2(x + sprite_texture->frame_width / 2, y + sprite_texture->frame_height / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMatrix, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMatrix = newMatrix * oldMatrix;
	kSpriteHandler->SetTransform(&finalMatrix);

	Draw(x, y);

	kSpriteHandler->SetTransform(&oldMatrix);
}

void Sprite::DrawFlipY(int x, int y)
{
	D3DXMATRIX oldMatrix;
	kSpriteHandler->GetTransform(&oldMatrix);

	D3DXMATRIX newMatrix;
	D3DXVECTOR2 center = D3DXVECTOR2(x + sprite_texture->frame_width / 2, y + sprite_texture->frame_height / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMatrix, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMatrix = newMatrix * oldMatrix;
	kSpriteHandler->SetTransform(&finalMatrix);

	Draw(x, y);

	kSpriteHandler->SetTransform(&oldMatrix);
}

void Sprite::DrawRect(int x, int y, RECT srcRect)
{
	D3DXVECTOR3 pos((float)x, (float)y, 0);

	kSpriteHandler->Draw(
		sprite_texture->picture,
		&srcRect,
		NULL,
		&pos,
		D3DCOLOR_XRGB(255, 255, 255));
}

void Sprite::DrawTransform(int x, int y, D3DXVECTOR2 scale, float degRotate, float depth)
{
	RECT srcRect;

	srcRect.left = (index % sprite_texture->num_cols) * (sprite_texture->frame_width);
	srcRect.top = (index / sprite_texture->num_rows) * (sprite_texture->frame_height);
	srcRect.right = srcRect.left + sprite_texture->frame_width;
	srcRect.bottom = srcRect.top + sprite_texture->frame_height;

	D3DXMATRIX oldMatrix;
	kSpriteHandler->GetTransform(&oldMatrix);

	D3DXMATRIX newMatrix;
	D3DXVECTOR2 center = D3DXVECTOR2(x + sprite_texture->frame_width / 2, y + sprite_texture->frame_height / 2);

	D3DXMatrixTransformation2D(
		&newMatrix,
		&center,
		0.0f,
		&scale,
		&center,
		D3DXToRadian(degRotate),
		NULL);

	D3DXMATRIX finalMatrix = newMatrix * oldMatrix;
	kSpriteHandler->SetTransform(&finalMatrix);

	kSpriteHandler->Draw(
		sprite_texture->picture,
		&srcRect,
		NULL,
		&D3DXVECTOR3(x, y, depth),
		0xFFFFFFFF);

	kSpriteHandler->SetTransform(&oldMatrix);
}
