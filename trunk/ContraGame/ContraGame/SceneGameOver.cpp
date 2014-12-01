#include "SceneGameOver.h"

#include "ScenePause.h"

SceneGameOver::SceneGameOver()
	:BaseScene()
{
	m_timeDuring = 100;
	init();

}

SceneGameOver::~SceneGameOver()
{

}

void SceneGameOver::processInput()
{

}

void SceneGameOver::init()
{
	m_sp1P = new CSprite(m_resource->load_1p);
	m_sp1P->setPostion(D3DXVECTOR2(20, 40));


	m_spHi = new CSprite(m_resource->load_hi);
	m_spHi->setPostion(D3DXVECTOR2(80, 90));

	m_spNumber = new CSprite(m_resource->load_number);



}

void SceneGameOver::draw()
{
	m_sp1P->Draw(m_sp1P->_pos);
	m_spHi->Draw(m_spHi->_pos);

	if (m_timeDuring % 10 == 0)
	{
		drawNumber("10000", 110, 90);
	}


}

void SceneGameOver::update(float time)
{

}

void SceneGameOver::drawNumber(string str, float posX, float posY)
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


void SceneGameOver::destroy()
{

}