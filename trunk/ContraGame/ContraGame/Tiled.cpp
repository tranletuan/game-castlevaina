#include "Tiled.h"


Tiled::Tiled()
{

}

Tiled::Tiled(int index, int id, float posX, float posY)
{	
	m_posX = posX;
	m_posY = posY;
	m_height = BG_TILED_HEIGTH;
	m_width = BG_TILED_WIDTH;
	m_id = id;
	m_index = index;
	init();	
}

void Tiled::init()
{
	m_level = CResourcesManager::GetInstance()->m_levelMap;
	m_camera = CResourcesManager::GetInstance()->_camera;
	// load sprite
	switch (m_level)
	{
	case 1:
		m_sprite = new CSprite(CResourcesManager::GetInstance()->background_1);
		break;
	case 2:
		m_sprite = new CSprite(CResourcesManager::GetInstance()->background_2);
		break;
	case 3:
		break;
	default:
		break;
	}
}



void Tiled::update(float time)
{

}

void Tiled::draw()
{
	int rows = m_sprite->sprite_texture->width / BG_TILED_WIDTH; // so hang cua image

	int left = (m_id % rows) * BG_TILED_WIDTH;
	int top = (m_id / rows)  * BG_TILED_HEIGTH;
	int right = left + BG_TILED_WIDTH;
	int bot = top + BG_TILED_HEIGTH;
	RECT rec = m_sprite->GetRect(left,top,right,bot);

	D3DXVECTOR2 pos = m_camera->Transform(m_posX, m_posY);

	m_sprite->Draw(pos.x,pos.y,rec);
}



Tiled::~Tiled()
{

}