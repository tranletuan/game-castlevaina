#include "SceneWin.h"

SceneWin::SceneWin()
{
	m_count = 0;
	m_pos = D3DXVECTOR2(130, 240);
	init();
}

SceneWin::~SceneWin()
{

}

void SceneWin::processInput()
{
	if (m_input->onKeyDown(DIK_RETURN))
	{
		if (m_count == 0)
		{
			m_pos.y = 30;
		}
		else if (m_count == 1)
		{
			m_nextScene = true;
		}
	}
}

void SceneWin::init()
{
	m_spCongru = new CSprite(CResourcesManager::GetInstance()->win_congra);
	m_spVictory = new CSprite(CResourcesManager::GetInstance()->win_victory);
	m_spLead = new CSprite(CResourcesManager::GetInstance()->win_lead);
	m_spThay = new CSprite(CResourcesManager::GetInstance()->win_thay);
	m_spPro = new CSprite(CResourcesManager::GetInstance()->win_product);
	m_spTien = new CSprite(CResourcesManager::GetInstance()->win_tien);
	m_spTuan = new CSprite(CResourcesManager::GetInstance()->win_tuan);
	m_spCopy = new CSprite(CResourcesManager::GetInstance()->win_copy);

	m_music_bg = m_resource->music_win_bg;
	m_audio->playSound(m_music_bg);

}

void SceneWin::draw()
{
	drawBackground(m_pos);
}

void SceneWin::drawBackground(D3DXVECTOR2 pos)
{
	D3DXVECTOR2 posCongru = D3DXVECTOR2(pos.x - 60, pos.y);
	m_spCongru->setPostion(posCongru);
	m_spCongru->Draw(m_spCongru->_pos);

	D3DXVECTOR2 posVictory = D3DXVECTOR2(pos.x - 40, pos.y + 40);
	m_spVictory->setPostion(posVictory);
	m_spVictory->Draw(m_spVictory->_pos);

	D3DXVECTOR2 posLead = D3DXVECTOR2(pos.x - 90, pos.y + 70);
	m_spLead->setPostion(posLead);
	m_spLead->Draw(m_spLead->_pos);

	D3DXVECTOR2 posThay = D3DXVECTOR2(pos.x - 40, pos.y + 90);
	m_spThay->setPostion(posThay);
	m_spThay->Draw(m_spThay->_pos);

	D3DXVECTOR2 posPro = D3DXVECTOR2(pos.x - 95, pos.y + 110);
	m_spPro->setPostion(posPro);
	m_spPro->Draw(m_spPro->_pos);

	D3DXVECTOR2 posTien = D3DXVECTOR2(pos.x - 50, pos.y + 130);
	m_spTien->setPostion(posTien);
	m_spTien->Draw(m_spTien->_pos);

	D3DXVECTOR2 posTuan = D3DXVECTOR2(pos.x - 50, pos.y + 150);
	m_spTuan->setPostion(posTuan);
	m_spTuan->Draw(m_spTuan->_pos);

	D3DXVECTOR2 posCopy = D3DXVECTOR2(pos.x - 50, pos.y + 180);
	m_spCopy->setPostion(posCopy);
	m_spCopy->Draw(m_spCopy->_pos);
}

void SceneWin::update(float time)
{
	if (m_nextScene)
	{
		m_audio->stopSound(m_music_bg);
		m_resource->readFileConfiDefault();
		SceneManager::getInstance()->createMenuScene();
	}

	if (m_count == 0)
	{
		if (m_pos.y > 30)
		{
			m_pos.y -= 1;
		}
		else
		{
			m_pos.y = 30;
			m_count = 1;
		}
	}


}

void SceneWin::destroy()
{

}