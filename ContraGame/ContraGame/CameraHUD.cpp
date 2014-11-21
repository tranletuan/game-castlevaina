#include "CameraHUD.h"

CameraHUD::CameraHUD()
{	
	init();
}

CameraHUD::CameraHUD(int life)
{
	m_life = life;	
	init();
}

CameraHUD::~CameraHUD()
{

}

void CameraHUD::draw()
{
	// ve huy chuong
	for (int i = 0; i < m_life; i++)
	{	
		D3DXVECTOR2 pos = D3DXVECTOR2(20 + i*SPACE_BADGE, 20);
		m_sprite->setPostion(pos);
		m_sprite->Draw(pos);
	}
}

void CameraHUD::update(float time)
{
	m_life = CResourcesManager::GetInstance()->m_life;
}

void CameraHUD::init()
{
	m_sprite = new CSprite(CResourcesManager::GetInstance()->HUD_badge);	
	m_life = CResourcesManager::GetInstance()->m_life;
}

