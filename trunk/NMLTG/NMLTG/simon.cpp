#include "simon.h"

Simon::Simon(D3DXVECTOR2 pos)
{
	this->pos = pos;
	sprite_normal = NULL;
	vx_last = 1;
}

Simon::~Simon()
{
	/*if (sprite_normal != NULL)
		delete sprite_normal;*/
}
void Simon::LoadResources()
{
	sprite_normal = new Sprite(new Texture(L"H:\\Users\\Tran\\Desktop\\normal.png", 9, 1, 9), 10);
}

void Simon::Update(int delta)
{
	//Cập nhật các trạng thái của simon

	//Tọa độ
	pos.x += vx * delta;
	pos.y += vy * delta;

	//simon rơi khi không chạm đất
	//hoặc giữ tọa độ y trên mặt đất
	if (pos.y - 32 > kGround)
	{
		vy -= VECTOR_G;
	}
	else
	{
		vy = 0;
		pos.y = kGround + 32;
	}

	

}

void Simon::Draw(Camera camera)
{
	D3DXVECTOR3 pos_transfer = camera.Transform(pos.x, pos.y);
	
	//Vẽ simon theo trạng thái hiện tại của simon
	//Cập nhật trạng thái của simon
	switch (status)
	{
	case SIMON_STAND:
		sprite_normal->SelectFrameOf(0);
		break;

	case SIMON_MOVE_LEFT:
		sprite_normal->UpdateEffect(0, 2, 65);
		break;

	case SIMON_MOVE_RIGHT:
		sprite_normal->UpdateEffect(0, 2, 65);
		break;

	case SIMON_MOVE_UP:
		sprite_normal->UpdateEffect(4, 6, 70);

		break;

	case SIMON_STOOP:
		break;

	case SIMON_JUMP:
		sprite_normal->SelectFrameOf(3);
		break;

	case SIMON_USE_CANE:
		break;
	case SIMON_STOOP_USE_CANE:
		break;
	case SIMON_USE_ITEM:
		break;
	default:
		break;
	}

	if (vx_last < 0)
		sprite_normal->Draw(pos_transfer.x, pos_transfer.y);
	else
		sprite_normal->DrawFlipX(pos_transfer.x, pos_transfer.y);
}

void Simon::Stand()
{
	status = SIMON_STAND;
	vx = vy = 0;
}

void Simon::MoveLeft()
{
	vx = -VECTOR_V;
	vx_last = vx;
	if (status == SIMON_STAND || status == SIMON_MOVE_RIGHT)
	{
		status = SIMON_MOVE_LEFT;
	}
		
}

void Simon::MoveRight()
{
	vx = VECTOR_V;
	vx_last = vx;
	if (status == SIMON_STAND || status == SIMON_MOVE_LEFT)
	{
		status = SIMON_MOVE_RIGHT;
	}
}

void Simon::MoveUp()
{
	vx = vx_last;
	status = SIMON_MOVE_UP;
}

void Simon::Jump()
{
	if (pos.y - 32 <= kGround)
	{
		vy = VECTOR_G * 6;
	}
	
	status = SIMON_JUMP;
}

void Simon::Stoop()
{
	vx = vy = 0;
	status = SIMON_STOOP;
}



