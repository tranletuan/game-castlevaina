#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	m_background = new Background();
	m_cameraHUD = new CameraHUD(3);
	m_tree = new QTTree();
	
	_weapon_player1 = new CPlayerWeapon();
	_player1 = new CBill(1231, Player1, D3DXVECTOR3(0, 200, 0), 32, 32);
	_player1->SetWeapon(_weapon_player1);


	init();
}

ScenePlay::~ScenePlay()
{

}

void ScenePlay::processInput()
{
	_player1->ProcessInput();
}

void ScenePlay::init()
{
	m_camera = m_resource->_camera;
}

void ScenePlay::update(float time)
{
	UpdateFullListObjetcInView();
	ProcessGroundsWithOneAnother();
	ProcessEnemiesWithOneAnother();
	ProcessItemsWithOneAnother();

	m_background->update(time);
	m_tree->update(time);

	_player1->Update(time);
	_weapon_player1->Update(time);

	
	m_cameraHUD->update(time);
	m_camera->Update(_player1->getPosX(), _player1->getPosY());

	UpdateGlobalVariable();
}

void ScenePlay::draw()
{
	//m_background->draw();
	m_tree->draw();
	_weapon_player1->Draw();
	_player1->Draw();
	m_cameraHUD->draw();
}

void ScenePlay::destroy()
{

}

void ScenePlay::UpdateFullListObjetcInView()
{
	vector<CObject*> objects = CResourcesManager::GetInstance()->listObinView;

	if (objects.size() > 0)
	{
		_grounds.clear();
		_enemies.clear();
		_items.clear();

		for (vector<CObject*>::iterator i = objects.begin(); i != objects.end(); i++)
		{
			CObject* ob = (*i);
			switch (ob->_basic_type)
			{
			case Ground:
				_grounds[ob->_id] = ob;
				break;
			case Enemy:
				if (ob->_hp > 0)
					_enemies[ob->_id] = ob;
				break;
			case Item:
				if (ob->_hp > 0)
					_items[ob->_id] = ob;
				break;
			}
		}
	}
}

void ScenePlay::ProcessGroundsWithOneAnother()
{
	if (_grounds.size() > 0)
	{
		CollisionDirection collision_player1 = Undefined;
		CollisionDirection collision_player2 = Undefined;
		for (map<int, CObject*>::iterator i = _grounds.begin(); i != _grounds.end(); i++)
		{
			CObject* ground = (*i).second;
			//Xét va chạm với người chơi 1
			if (_player1->GetIdGroundIgnore() != ground->_id && collision_player1 != TopCollision)
			{
				collision_player1 = _player1->_physical.Collision(&ground->_physical);
				if (collision_player1 == TopCollision && _player1->_physical.current_vy < 0)
				{
					_player1->Standing(ground->_physical.bounds.top + BILL_BOUNDS_HEIGHT / 2 + 0.5f, ground->_id);
					if (ground->_specific_type == Ground_Water)
					{
						_player1->SetEnviroment(Water);
					}
					else
					{
						_player1->SetEnviroment(Land);
					}
				}
			}

			//Xét va chạm với người chơi 2

			//Xét va chạm với items

			//Xét va chạm với các đối tượng k có trong quadtree
		}

		if (collision_player1 != TopCollision)
		{
			_player1->_physical.n = 0;
		}


	}
}

void ScenePlay::ProcessEnemiesWithOneAnother()
{}

void ScenePlay::ProcessItemsWithOneAnother()
{}

void ScenePlay::UpdateGlobalVariable()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	rs->m_posBill.x = _player1->_physical.x;
	rs->m_posBill.y = _player1->_physical.y;
	rs->_grounds = _grounds;
}