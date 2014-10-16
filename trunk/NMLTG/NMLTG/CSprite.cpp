#include "CSprite.h"
#include "global.h"

CSprite::CSprite()
{
	sprite_texture = NULL;
	start = 0;
	end = 0;
	index = 0;
	time_ani = 0;
	last_time = 0;
}

CSprite::CSprite(const CSprite &sprite)
{
	sprite_texture = sprite.sprite_texture;
	start = sprite.start;
	end = sprite.end;
	index = sprite.index;
	time_ani = sprite.time_ani;
	last_time = sprite.last_time;
}

CSprite::CSprite(CTexture *texture, int start, int end, int time_ani) 
: sprite_texture(texture)
{
	this->start = start;
	this->end = end;
	this->index = start;
	this->time_ani = time_ani;
	this->last_time = 0;
}

CSprite::CSprite(CTexture *texture, int time_ani) :sprite_texture(texture)
{
	this->start = 0;
	this->end = texture->count - 1;
	this->time_ani = time_ani;
	this->index = 0;
	this->last_time = 0;
}

CSprite::~CSprite()
{

}

void CSprite::Next()
{
	index++;
	if (index > end)
	{
		index = start;
	}
}

void CSprite::Reset()
{
	index = start;
	last_time = 0;
}

void CSprite::SelectFrameOf(int index)
{
	this->index = index;
	if (index > sprite_texture->count)
		Reset();
}

void CSprite::UpdateAllEffect(int elapsed_time)
{
	DWORD now = GetTickCount();
	time_ani = elapsed_time;

	if (now - last_time >= time_ani)
	{
		Next();
		last_time = now;
	}
}

void CSprite::UpdateEffect()
{
	if (start < end)
	{
		DWORD now = GetTickCount();

		if (now - last_time >= time_ani)
		{
			index = index + 1 > end ? start : index + 1;
			last_time = now;
		}
	}
}

void CSprite::Draw(int x, int y)
{
	RECT src_rect;

	src_rect.left = (index % sprite_texture->num_cols) * (sprite_texture->frame_width);
	src_rect.top = (index / sprite_texture->num_cols) * (sprite_texture->frame_height);
	src_rect.right = src_rect.left + sprite_texture->frame_width;
	src_rect.bottom = src_rect.top + sprite_texture->frame_height;

	D3DXVECTOR3 pos = GetCorner(x, y, sprite_texture->frame_width, sprite_texture->frame_height);

	kSpriteHandler->Draw(
		sprite_texture->picture,
		&src_rect,
		NULL,
		&pos,
		D3DCOLOR_XRGB(255, 255, 255));
}

void CSprite::DrawFlipX(int x, int y)
{
	RECT src_rect;

	src_rect.left = (index % sprite_texture->num_cols) * (sprite_texture->frame_width);
	src_rect.top = (index / sprite_texture->num_cols) * (sprite_texture->frame_height);
	src_rect.right = src_rect.left + sprite_texture->frame_width;
	src_rect.bottom = src_rect.top + sprite_texture->frame_height;

	D3DXMATRIX old_matrix;
	kSpriteHandler->GetTransform(&old_matrix);

	D3DXMATRIX new_natrix;
	D3DXVECTOR2 center = D3DXVECTOR2(x + sprite_texture->frame_width / 2, y + sprite_texture->frame_height / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&new_natrix, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMatrix = new_natrix * old_matrix;
	kSpriteHandler->SetTransform(&finalMatrix);

	Draw(x, y);

	kSpriteHandler->SetTransform(&old_matrix);
}

void CSprite::DrawFlipY(int x, int y)
{
	RECT src_rect;

	src_rect.left = (index % sprite_texture->num_cols) * (sprite_texture->frame_width);
	src_rect.top = (index / sprite_texture->num_cols) * (sprite_texture->frame_height);
	src_rect.right = src_rect.left + sprite_texture->frame_width;
	src_rect.bottom = src_rect.top + sprite_texture->frame_height;

	D3DXMATRIX old_matrix;
	kSpriteHandler->GetTransform(&old_matrix);

	D3DXMATRIX new_natrix;
	D3DXVECTOR2 center = D3DXVECTOR2(x + sprite_texture->frame_width / 2, y + sprite_texture->frame_height / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&new_natrix, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMatrix = new_natrix * old_matrix;
	kSpriteHandler->SetTransform(&finalMatrix);

	Draw(x, y);

	kSpriteHandler->SetTransform(&old_matrix);
}

void CSprite::DrawRect(int x, int y, RECT srcRect)
{
	D3DXVECTOR3 pos((float)x, (float)y, 0);

	kSpriteHandler->Draw(
		sprite_texture->picture,
		&srcRect,
		NULL,
		&pos,
		D3DCOLOR_XRGB(255, 255, 255));
}

void CSprite::DrawTransform(int x, int y, D3DXVECTOR2 scale, float degRotate, float depth)
{
	RECT src_rect;

	src_rect.left = (index % sprite_texture->num_cols) * (sprite_texture->frame_width);
	src_rect.top = (index / sprite_texture->num_cols) * (sprite_texture->frame_height);
	src_rect.right = src_rect.left + sprite_texture->frame_width;
	src_rect.bottom = src_rect.top + sprite_texture->frame_height;

	D3DXMATRIX old_matrix;
	kSpriteHandler->GetTransform(&old_matrix);

	D3DXMATRIX new_natrix;
	D3DXVECTOR2 center = D3DXVECTOR2(x + sprite_texture->frame_width / 2, y + sprite_texture->frame_height / 2);

	D3DXMatrixTransformation2D(
		&new_natrix,
		&center,
		0.0f,
		&scale,
		&center,
		D3DXToRadian(degRotate),
		NULL);

	D3DXMATRIX final_matrix = new_natrix * old_matrix;
	kSpriteHandler->SetTransform(&final_matrix);
	D3DXVECTOR3 pos = GetCorner(x, y, sprite_texture->frame_width, sprite_texture->frame_height);

	kSpriteHandler->Draw(
		sprite_texture->picture,
		&src_rect,
		NULL,
		&D3DXVECTOR3(pos.x, pos.y, depth),
		0xFFFFFFFF);

	kSpriteHandler->SetTransform(&old_matrix);
}

void CSprite::DrawWithDirecion(D3DXVECTOR3 pos, float direction, int start, int end, int time)
{
	this->start = start;
	this->end = end;
	this->time_ani = time;

	if (direction > 0)
	{
		Draw(pos.x, pos.y);
	}
	else
	{
		DrawFlipX(pos.x, pos.y);
	}
}

D3DXVECTOR3 CSprite::GetCorner(int x, int y, int width, int height)
{
	return D3DXVECTOR3(x - width / 2, y - height / 2, 0);
}