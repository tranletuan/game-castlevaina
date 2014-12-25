#include "CRockFly.h"

CRockFly::CRockFly(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CGround(id, specific_type, pos, width, height)
{	
	_direction = 1;
	LoadResources();
	_posXBegin = (pos.x - width / 2) + _current_sprite->sprite_texture->width / 2;
	_posXEnd = (pos.x + width / 2) - _current_sprite->sprite_texture->width / 2;

}

CRockFly::~CRockFly()
{

}

void CRockFly::LoadResources()
{
	_current_sprite = new CSprite(CResourcesManager::GetInstance()->_ground_rock_fly);
	_current_sprite->SelectFrameOf(0);
}

void CRockFly::Draw()
{
	D3DXVECTOR3 pos = CResourcesManager::GetInstance()->_camera->Transform(_physical.x, _physical.y);
	DrawMove(pos);

}

void CRockFly::DrawMove(D3DXVECTOR3 pos)
{
	_current_sprite->Draw(pos.x, pos.y);
}

void CRockFly::Update(int delta_time)
{
	_physical.SetBounds(_physical.x, _physical.y, 28, 30);
	// Đi ra tọa độ kết thúc
	if (_physical.x >= _posXEnd )
	{
		_direction = -1;
	}
	// Đi ra tọa độ bắt đầu
	else if (_physical.x <= _posXBegin )
	{
		_direction = 1;
	}

	_physical.vx = GROUND_ROCK_FLY_VX * _direction;
	_physical.vy = 0;
	_physical.CalcPositionWithoutGravitation(delta_time);


}