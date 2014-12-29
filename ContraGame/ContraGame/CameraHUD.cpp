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


	//Vẽ hiệu ứng item kill
	if (CResourcesManager::GetInstance()->m_effecKill > 0)
	{
		bool done = m_spriteEffectKill->PerformEffectOneTime(0, 2, 100);
		D3DXVECTOR2 pos = D3DXVECTOR2(0, 0);
		m_spriteEffectKill->setPostion(pos);
		m_spriteEffectKill->Draw(pos);

		if (done)
		{
			CResourcesManager::GetInstance()->m_effecKill--;
			m_spriteEffectKill->Reset();
		}
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
	m_spriteEffectKill = new CSprite(CResourcesManager::GetInstance()->HUD_effect_kill);
	m_life = CResourcesManager::GetInstance()->m_life;
}

