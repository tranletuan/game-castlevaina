#include "Background.h"

Background::Background()
{
	m_beginRow = 0;
	m_beginCol = 0;
	m_endCol = 0;
	m_endRow = 0;
	init();
}



void Background::draw()
{
	for (int row = m_beginRow; row < m_endRow; row++) {
		for (int col = m_beginCol; col < m_endCol; col++) {
			int index = row * m_cols + col;
			m_listTiled.at(index)->draw();
		}
	}

}

void Background::init()
{
	m_camera = CResourcesManager::GetInstance()->_camera;
	m_level = CResourcesManager::GetInstance()->m_levelMap;

	switch (m_level)
	{
	case 1:
		m_listBG = CResourcesManager::GetInstance()->map1_bg_listTile;
		break;
	case 2:
		m_listBG = CResourcesManager::GetInstance()->map2_bg_listTile;
		break;
	default:
		break;
	}

	// lay chieu dai va chieu rong cua background
	m_cols = m_listBG.at(0);
	m_rows = m_listBG.at(1);
	m_listBG.erase(m_listBG.begin() + 0);
	m_listBG.erase(m_listBG.begin() + 0);

	m_width = m_cols * BG_TILED_WIDTH;
	m_height = m_rows * BG_TILED_HEIGTH;

	// list tiled
	for (int row = 0; row < m_rows; row++) {
		for (int col = 0; col < m_cols; col++) {

			int id = m_listBG.at(row * m_cols + col);
			int posX = BG_TILED_WIDTH*col;
			int posY = m_height - row*BG_TILED_HEIGTH;
			Tiled *tile = new Tiled(m_listTiled.size(), id, posX, posY);

			m_listTiled.push_back(tile);
		}
	}

}

void Background::update(float time)
{

	// update ve theo camera, 
	m_beginRow = (m_height - m_camera->getPosY()) / BG_TILED_HEIGTH;
	m_beginCol = m_camera->getPosX() / BG_TILED_WIDTH;
	m_endCol = m_beginCol + m_camera->getWidth() / BG_TILED_WIDTH;
	m_endRow = m_beginRow + m_camera->getHeight() / BG_TILED_HEIGTH;
	if (m_beginRow > 1)
	{
		m_beginRow -= 2;
	}
	if (m_beginCol > 1)
	{
		m_beginCol -= 2;
	}
	if (m_endCol < m_cols - 1)
	{
		m_endCol += 2;
	}
	if (m_endRow < m_rows - 1)
	{
		m_endRow += 2;
	}

}

Background::~Background()
{

}






