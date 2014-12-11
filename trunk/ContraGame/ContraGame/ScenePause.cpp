#include "ScenePause.h"

ScenePause::ScenePause()
	:BaseScene()
{
	m_timeDuring = 100;
	m_timeCount = 0;
	m_curItem = Item1;
	m_checkItem = false;
	init();

}

ScenePause::~ScenePause()
{

}

void ScenePause::processInput()
{
	// enter
	if (m_input->onKeyDown(DIK_RETURN))
	{
		m_checkItem = true;
	}

	// phim up
	if (m_input->onKeyDown(DIK_UPARROW))
	{		
		clickMenuItem();
	}

	// phim down arrow
	if (m_input->onKeyDown(DIK_DOWNARROW))
	{
		clickMenuItem();
	}

}

void ScenePause::init()
{
	m_sp1P = new CSprite(m_resource->load_1p);
	m_sp1P->setPostion(D3DXVECTOR2(20, 20));

	m_spHi = new CSprite(m_resource->load_hi);
	m_spHi->setPostion(D3DXVECTOR2(80, 70));

	m_spRest = new CSprite(m_resource->load_rest);
	m_spRest->setPostion(D3DXVECTOR2(20, 40));

	m_spTitle = new CSprite(m_resource->pause_title);
	m_spTitle->setPostion(D3DXVECTOR2(80, 130));

	m_spConti = new CSprite(m_resource->pause_continue);
	m_spConti->setPostion(D3DXVECTOR2(120, 160));

	m_spEnd = new CSprite(m_resource->pause_end);
	m_spEnd->setPostion(D3DXVECTOR2(120, 180));

	m_spBadge = new CSprite(m_resource->menu_badge);
	m_spBadge->setPostion(D3DXVECTOR2(100, 160));


	m_spNumber = new CSprite(m_resource->load_number);


	switch (CResourcesManager::GetInstance()->m_levelMap)
	{
	case 1:
		m_spStage = new CSprite(m_resource->load_stage1);
		m_spNameStage = new CSprite(m_resource->load_nameStage1);
		break;
	case 2:
		m_spStage = new CSprite(m_resource->load_stage2);
		m_spNameStage = new CSprite(m_resource->load_nameStage2);
		break;
	case 3:
		m_spStage = new CSprite(m_resource->load_stage3);
		m_spNameStage = new CSprite(m_resource->load_nameStage3);
		break;
	default:
		break;
	}

	m_spNameStage->setPostion(D3DXVECTOR2(100, 110));
	m_spStage->setPostion(D3DXVECTOR2(100, 90));
}

void ScenePause::draw()
{
	m_sp1P->Draw(m_sp1P->_pos);
	m_spHi->Draw(m_spHi->_pos);
	m_spBadge->Draw(m_spBadge->_pos);
	m_spRest->Draw(m_spRest->_pos);
	m_spStage->Draw(m_spStage->_pos);
	m_spNameStage->Draw(m_spNameStage->_pos);
	m_spTitle->Draw(m_spTitle->_pos);

	// ve so
	int delta = m_timeCount % 15;
	if (m_timeCount % 15 > 4 && m_timeCount % 15 < 15)
	{
		drawNumber(to_string(m_resource->m_numScore), 100, 25);
		drawNumber(to_string(m_resource->m_highScore), 110, 75);
		drawNumber(to_string(m_resource->m_life), 70, 45);
	}
	// ve hieu ung button
	if (!m_checkItem)
	{
		m_spConti->Draw(m_spConti->_pos);
		m_spEnd->Draw(m_spEnd->_pos);
	}
	else
	{
		if (m_curItem == Item1)
		{
			m_spEnd->Draw(m_spEnd->_pos);
			if (m_timeDuring % 15 > 5 && m_timeDuring % 15 < 10)
			{
				m_spConti->Draw(m_spConti->_pos);
			}
		}
		else if (m_curItem == Item2)
		{
			m_spConti->Draw(m_spConti->_pos);
			if (m_timeDuring % 15 > 5 && m_timeDuring % 15 < 10)
			{
				m_spEnd->Draw(m_spEnd->_pos);
			}
		}
	}
}

void ScenePause::update(float time)
{
	m_timeCount++; 
	if (m_timeCount > 5000)
	{
		m_timeCount = 0;
	}

	// xu ly check item (da bam)
	if (m_checkItem)
	{
		if (m_timeDuring > 0)
		{
			m_timeDuring--;
		}
		else
		{
			m_nextScene = true;
			m_checkItem = false;
		}

	}
	// xu ly next scene
	if (m_nextScene)
	{
		if (m_curItem == Item1)
		{
			SceneManager::getInstance()->loadPlayScene();
		}
		else if (m_curItem == Item2)
		{
			SceneManager::getInstance()->createMenuScene();
		}		
	}
	
}

void ScenePause::drawNumber(string str, float posX, float posY)
{
	int length = str.length();
	int begin = 0;
	int end = 0;
	float x = posX;
	string token = "";
	int distance_number = 10;
	for (int i = 0; i < length; i++)
	{
		begin = i;
		end = begin + 1;
		token = str.substr(begin, end);
		m_spNumber->SelectFrameOf(atoi(token.c_str()));
		m_spNumber->Draw(x, posY);
		x += distance_number;
	}

}

void ScenePause::clickMenuItem()
{
	if (!m_checkItem)
	{
		D3DXVECTOR2 posBadge = m_spBadge->_pos;
		// trang thai chon item
		switch (m_curItem)
		{
		case Item1:
			m_curItem = Item2;
			posBadge = D3DXVECTOR2(100, 180);
			break;
		case Item2:
			m_curItem = Item1;
			posBadge = D3DXVECTOR2(100, 160);
			break;
		default:
			break;
		}
		m_spBadge->setPostion(posBadge);
	}

}

void ScenePause::destroy()
{

}