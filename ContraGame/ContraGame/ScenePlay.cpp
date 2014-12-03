#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	m_background = new Background();
	m_cameraHUD = new CameraHUD(3);
	m_bill = new CBill();
	m_tree = new QTTree();
	m_playerWeapon = new CPlayerWeapon();
	m_enemyWeapon = new CEnemyWeapon();
	m_enemy_test = new CSniperHide(123, Sniper_Hide, D3DXVECTOR3(200, 142, 0), 26, 44);
	m_enemy_test->SetWeapon(m_enemyWeapon);
	m_listNoTree = new CListNoTree();	
	
	init();
}

ScenePlay::~ScenePlay()
{

}

void ScenePlay::processInput()
{
	m_bill->ProcessInput();

	// test
	m_camera->processInput();
	if (m_input->onKeyDown(DIK_P))
	{
		m_boss->_hp--;
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

	m_enemy_test->SetTarget(100, 50);
	m_enemy_test->Update(time);

	m_bill->Update(time);
	//m_camera->update(time, ResourceManager::getInstance()->m_posChar);
	m_camera->Update(m_bill->getPosX(), m_bill->getPosY());

	m_listNoTree->Update(time);
	m_tree->update(time);
	m_cameraHUD->update(time);


}

void ScenePlay::draw()
{
	m_background->draw();
	m_tree->draw();
	m_bill->Draw();
	m_enemy_test->Draw();
	m_cameraHUD->draw();
	m_enemyWeapon->Draw();
	m_listNoTree->Draw();
	
}

void ScenePlay::destroy()
{

}