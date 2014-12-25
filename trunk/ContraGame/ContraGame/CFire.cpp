#include "CFire.h"

CFire::CFire(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CObject(id, specific_type, Enemy, pos, width, height)
{
	_init = true;
	_can_impact = true;
	LoadResources();
}

CFire::~CFire()
{

}

void CFire::LoadResources()
{	
	rs = CResourcesManager::GetInstance();
	_current_sprite = new CSprite(rs->_enemy_fire);	
}

void CFire::Draw()
{
	D3DXVECTOR3 pos = CResourcesManager::GetInstance()->_camera->Transform(_physical.x, _physical.y);
	DrawMove(pos);
}

void CFire::DrawMove(D3DXVECTOR3 pos)
{
	_current_sprite->DrawWithDirection(pos, 1, 0, 2, 200);
}

void CFire::Update(int delta_time)
{
	// cai dat toa do
	if (_init)
	{		
		for (int i = 0; i < rs->listObinView.size(); i++)
		{
			if (rs->listObinView.at(i)->getSpecificType() == Ground_Electron)
			{
				float posCenter = rs->listObinView.at(i)->_physical.x ;
				CTexture *texture = rs->listObinView.at(i)->getSprite()->sprite_texture;
				_physical.y = rs->listObinView.at(i)->_physical.y + texture->frame_height / 2;

				if (_physical.x <= posCenter)
				{
					_direction = 1;
					setTrack(Track_LR);
					_physical.x = rs->listObinView.at(i)->_physical.x - texture->frame_width/2 + _current_sprite->sprite_texture->frame_width / 2;					
				}
				else
				{
					_direction = -1;					
					_physical.x = rs->listObinView.at(i)->_physical.x + texture->frame_width / 2 - _current_sprite->sprite_texture->frame_width / 2;					
				}
				_posXEnd = rs->listObinView.at(i)->_physical.x + texture->frame_width / 2 - _current_sprite->sprite_texture->frame_width / 2;
				_posXBegin = rs->listObinView.at(i)->_physical.x - texture->frame_width / 2 + _current_sprite->sprite_texture->frame_width / 2;
				_init = false;
				break;
			}
		}
	}
	_physical.SetBounds(_physical.x, _physical.y, 16, 16);
	// Đi ra tọa độ kết thúc
	if (_physical.x > _posXEnd)
	{
		_direction = -1;
	}
	// Đi ra tọa độ bắt đầu
	else if (_physical.x < _posXBegin)
	{
		_direction = 1;
	}

	_physical.vx = ENEMY_FIRE_VX * _direction;
	_physical.vy = 0;
	_physical.CalcPositionWithoutGravitation(delta_time);
}