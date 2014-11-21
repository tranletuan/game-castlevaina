#include "BaseScene.h"

BaseScene::BaseScene()
{	
	m_resource = CResourcesManager::GetInstance();
	m_timeDuring = 0;
	m_input = CResourcesManager::GetInstance()->m_input;
	m_nextScene = false;
	m_backScene = false;
	m_audio = CResourcesManager::GetInstance()->m_audio;
	m_onSound = false;
}

BaseScene::~BaseScene()
{

}

void BaseScene::destroy()
{

}

void BaseScene::init()
{

}

void BaseScene::processInput()
{

}

void BaseScene::draw()
{

}

void BaseScene::update(float time)
{

}



