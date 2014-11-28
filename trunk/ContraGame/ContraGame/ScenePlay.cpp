#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	m_background = new Background();
	m_cameraHUD = new CameraHUD(3);
	m_bill = new CBill();
	m_tree = new QTTree();
	m_playerWeapon = new CPlayerWeapon();
	m_enemyWeapon = new CEnemyWeapon();
	m_enemy_test = new CWallTurret(123, Wall_Turret, D3DXVECTOR3(130, 100, 0), 32, 32);
	m_enemy_test->SetWeapon(m_enemyWeapon);
	m_bill->_physical.vx = 0.05f;
	m_bill->_physical.vy = 0.1f;
	init();
}

ScenePlay::~ScenePlay()
{

}

int x, y;
void ScenePlay::processInput()
{
	m_bill->ProcessInput();
	

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

	if (m_bill->_physical.x > 256 || m_bill->_physical.x < 0)
	{
		m_bill->_physical.vx *= -1;
	}

	if (m_bill->_physical.y > 240 || m_bill->_physical.y < 0)
	{
		m_bill->_physical.vy *= -1;
	}
	m_bill->_physical.CalcPositionWithoutGravitation(time);

	m_enemy_test->SetTarget(m_bill->_physical.x, m_bill->_physical.y);
	m_enemy_test->Update(time);
	
	//m_bill->Update(time);
	//m_camera->update(time, ResourceManager::getInstance()->m_posChar);
	//m_camera->Update(m_bill->getPosX(), m_bill->getPosY());
	m_cameraHUD->update(time);
}

void ScenePlay::draw()
{
	m_background->draw();
	//m_tree->draw();
	m_bill->Draw();
	m_enemy_test->Draw();
	m_cameraHUD->draw();
	m_enemyWeapon->Draw();
}

void ScenePlay::destroy()
{

}