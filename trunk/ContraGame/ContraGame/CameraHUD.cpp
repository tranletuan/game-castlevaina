#include "CameraHUD.h"

CameraHUD::CameraHUD()
{
	init();
}

CameraHUD::~CameraHUD()
{

}

void CameraHUD::draw()
{
	if (m_life > 0)
	{
		// ve huy chuong
		for (int i = 0; i < m_life; i++)
		{
			if (i < 4)
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(20 + i*SPACE_BADGE, 20);
				m_spriteBadge->setPostion(pos);
				m_spriteBadge->Draw(pos);
			}
		}
	}
	else
	{
		// sprite game over ve
		D3DXVECTOR2 pos = D3DXVECTOR2(20, 20);
		m_spriteOver->setPostion(pos);
		m_spriteOver->Draw(pos);
	}

}

void CameraHUD::update(int time)
{
	m_life = CResourcesManager::GetInstance()->m_life;
}

void CameraHUD::init()
{
	m_spriteBadge = new CSprite(CResourcesManager::GetInstance()->HUD_badge);
	m_spriteOver = new CSprite(CResourcesManager::GetInstance()->HUD_gameover);
	m_life = CResourcesManager::GetInstance()->m_life;
}

