#include "SceneLoading.h"

SceneLoading::SceneLoading()
	:BaseScene()
{
	m_timeDuring = 100;
	init();

}

SceneLoading::~SceneLoading()
{

}

void SceneLoading::processInput()
{

	if (m_input->onKeyDown(DIK_RETURN))
	{
		m_backScene = true;
	}

}

void SceneLoading::init()
{
	m_sp1P = new CSprite(m_resource->load_1p);
	m_sp1P->setPostion(D3DXVECTOR2(20, 40));

	m_spRest = new CSprite(m_resource->load_rest);
	m_spRest->setPostion(D3DXVECTOR2(20, 60));

	m_spHi = new CSprite(m_resource->load_hi);
	m_spHi->setPostion(D3DXVECTOR2(80, 90));

	m_spNumber = new CSprite(m_resource->load_number);
	//m_spNumber->setPostion(D3DXVECTOR2(110, 90));

	m_spStage = new CSprite(m_resource->load_stage);
	m_spStage->setPostion(D3DXVECTOR2(100, 130));

	m_spNameStage = new CSprite(m_resource->load_nameStage);
	m_spNameStage->setPostion(D3DXVECTOR2(100, 150));

}

void SceneLoading::draw()
{
	m_sp1P->Draw(m_sp1P->_pos);
	m_spHi->Draw(m_spHi->_pos);
	m_spRest->Draw(m_spRest->_pos);
	m_spStage->Draw(m_spStage->_pos);
	m_spNameStage->Draw(m_spNameStage->_pos);
	/*if (m_timeDuring % 10 == 0)
	{
	drawNumber("10000", 110, 90);
	}*/\

	
}

void SceneLoading::update(float time)
{
	if (m_nextScene)
	{
		SceneManager::getInstance()->createPlayScene();
		m_nextScene = false;
	}
	if (m_backScene)
	{
		SceneManager::getInstance()->loadMenuScene();
		m_backScene = false;
	}

	if (m_timeDuring > 0)
	{
		m_timeDuring--;
	}
	else
	{
		m_nextScene = true;
	}
}

void SceneLoading::drawNumber(string str, float posX, float posY)
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


void SceneLoading::destroy()
{

}