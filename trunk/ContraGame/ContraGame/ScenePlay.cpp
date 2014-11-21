#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	m_background = new Background();
	m_cameraHUD = new CameraHUD(3);
	m_bill = new CBill();
	m_tree = new QTTree();
	m_playerWeapon = new CPlayerWeapon();
	m_enemyWeapon = new CEnemyWaepon();
	init();
}

ScenePlay::~ScenePlay()
{

}

void ScenePlay::processInput()
{
	//m_character->processInput();
}

void ScenePlay::init()
{
	m_camera = m_resource->_camera;
}

void ScenePlay::update(float time)
{	
	m_background->update(time);	
	m_tree->update(time);
	//m_character->update(time);	
	//m_camera->update(time, ResourceManager::getInstance()->m_posChar);
	m_camera->UpdateCamera(0);
	m_cameraHUD->update(time);
}

void ScenePlay::draw()
{
	m_background->draw();
	m_tree->draw();
	//m_character->draw();
	m_cameraHUD->draw();
}


void ScenePlay::destroy()
{

}