#include "SceneMenu.h"

SceneMenu::SceneMenu()
	:BaseScene()
{
	m_deltaVec = D3DXVECTOR2(-1, 0);
	m_runBG = true;
	m_curItem = Item1;
	m_checkItem = false;
	m_timeDuring = 100;
	init();
}

SceneMenu::~SceneMenu()
{

}

void SceneMenu::init()
{
	m_spBG = new CSprite(m_resource->menu_bg);
	m_spBG->setPostion(D3DXVECTOR2(256, 15));

	m_spItem1 = new CSprite(m_resource->menu_item1);
	m_spItem1->setPostion(D3DXVECTOR2(286, 155));

	m_spItem2 = new CSprite(m_resource->menu_item2);
	m_spItem2->setPostion(D3DXVECTOR2(286, 170));

	m_spBadge = new CSprite(m_resource->menu_badge);
	m_spBadge->setPostion(D3DXVECTOR2(266, 155));

	m_music_bg = m_resource->music_menu_bg;
	
}

void SceneMenu::draw()
{

	m_spBG->Draw(m_spBG->_pos);
	m_spBadge->Draw(m_spBadge->_pos);
	if (!m_checkItem)
	{
		m_spItem1->Draw(m_spItem1->_pos);
		m_spItem2->Draw(m_spItem2->_pos);
	}
	else
	{
		//xu ly item nhap nhay
		if (m_curItem == Item1)
		{
			if (m_timeDuring % 15 > 5 && m_timeDuring % 15 < 10)
			{
				m_spItem1->Draw(m_spItem1->_pos);
			}
			m_spItem2->Draw(m_spItem2->_pos);
		}
		else
		{
			if (m_timeDuring % 15 > 5 && m_timeDuring % 15 < 10)
			{
				m_spItem2->Draw(m_spItem2->_pos);
			}
			m_spItem1->Draw(m_spItem1->_pos);
		}	

	}
	
}

void SceneMenu::update(float time)
{

	D3DXVECTOR2 posBg = m_spBG->_pos;
	D3DXVECTOR2 posBadge = m_spBadge->_pos;
	D3DXVECTOR2 posItem1 = m_spItem1->_pos;
	D3DXVECTOR2 posItem2 = m_spItem2->_pos;

	if (posBg.x < 30)
	{
		m_runBG = false;
	}

	if (m_runBG)
	{
		// di chuyen background
		posBg += m_deltaVec;
		m_spBG->setPostion(posBg);
		posBadge += m_deltaVec;
		m_spBadge->setPostion(posBadge);
		posItem1 += m_deltaVec;
		m_spItem1->setPostion(posItem1);
		posItem2 += m_deltaVec;
		m_spItem2->setPostion(posItem2);
	}
	else
	{
		
		
	}

	// sau khi bam nut
	if (m_checkItem)
	{
		if (m_timeDuring>0)
		{
			m_timeDuring--;
		}
		else
		{
			m_nextScene = true;
			m_checkItem = false;
		}
	}

	// next scene
	if (m_nextScene)
	{
		SceneManager::getInstance()->createLoadingScene();			
	}

}

void SceneMenu::destroy()
{

}

void SceneMenu::processInput()
{
	// phim enter
	if (m_input->onKeyDown(DIK_RETURN))
	{
		

		if (m_runBG)
		{
			defaulPostionBG();
		}
		else
		{
			// play nhac nen
			if (!m_onSound)
			{
				m_audio->playSound(m_music_bg);
			}
			m_onSound = true;

			m_checkItem = true;
		}
	}

	// phim up arrow
	if (m_input->onKeyDown(DIK_UPARROW))
	{
		if (m_runBG)
		{
			defaulPostionBG();
		}
		else
		{
			clickMenuItem();
		}
	}

	// phim down arrow
	if (m_input->onKeyDown(DIK_DOWNARROW))
	{
		if (m_runBG)
		{
			defaulPostionBG();
		}
		else
		{
			clickMenuItem();
		}
	}
}

void SceneMenu::defaulPostionBG()
{
	// set bg mac dinh
	m_runBG = false;
	m_spBG->setPostion(D3DXVECTOR2(30, 15));
	m_spItem1->setPostion(D3DXVECTOR2(60, 155));
	m_spItem2->setPostion(D3DXVECTOR2(60, 170));
	m_spBadge->setPostion(D3DXVECTOR2(39, 155));
	
}

void SceneMenu::clickMenuItem()
{
	if (!m_checkItem)
	{
		D3DXVECTOR2 posBadge = m_spBadge->_pos;
		// trang thai chon item
		switch (m_curItem)
		{
		case Item1:
			m_curItem = Item2;
			posBadge = D3DXVECTOR2(39, 170);
			break;
		case Item2:
			m_curItem = Item1;
			posBadge = D3DXVECTOR2(39, 155);
			break;
		default:
			break;
		}
		m_spBadge->setPostion(posBadge);
	}
	
}