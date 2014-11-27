#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	m_background = new Background();
	m_cameraHUD = new CameraHUD(3);
	m_bill = new CBill();
	m_tree = new QTTree();
	m_playerWeapon = new CPlayerWeapon();
	m_enemyWeapon = new CEnemyWeapon();
	m_enemy_test = new CGroundCanon(123, Ground_Canon, D3DXVECTOR3(180, 142, 0), 32, 32);
	m_enemy_test->SetWeapon(m_enemyWeapon);
	init();
}

ScenePlay::~ScenePlay()
{

}

int x, y;
void ScenePlay::processInput()
{
	m_bill->ProcessInput();

	if (m_input->KeyDown(DIK_1))
	{
		x = 100;
		y = 142;
	}
	if (m_input->KeyDown(DIK_2))
	{
		x = 100;
		y = 170;
	}

	if (m_input->KeyDown(DIK_3))
	{
		x = 100;
		y = 270;
	}

	if (m_input->KeyDown(DIK_4))
	{
		x = 400;
		y = 270;
	}
	if (m_input->KeyDown(DIK_5))
	{
		m_enemy_test->_hp = 0;
	}
	
}

void ScenePlay::init()
{
	m_camera = m_resource->_camera;
}

void ScenePlay::update(float time)
{	
	m_background->update(time);	
	m_tree->update(time);
	m_enemyWeapon->Update(time);

	m_enemy_test->SetTarget(x, y);
	m_enemy_test->Update(time);
	
	//m_bill->Update(time);
	//m_camera->update(time, ResourceManager::getInstance()->m_posChar);
	m_camera->UpdateCamera(m_bill->getPosX());
	m_cameraHUD->update(time);
}

void ScenePlay::draw()
{
	m_background->draw();
	//m_tree->draw();
	//m_bill->Draw();
	m_enemy_test->Draw();
	m_cameraHUD->draw();
	m_enemyWeapon->Draw();
}

void ScenePlay::destroy()
{

}