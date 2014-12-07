﻿#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	m_background = new Background();
	m_cameraHUD = new CameraHUD(3);
	m_tree = new QTTree();
	
	_weapon_player1 = new CPlayerWeapon();
	_player1 = new CBill();
	_player1->_physical.x = 1300;
	_player1->SetWeapon(_weapon_player1);

	_weapon_enemy = new CEnemyWeapon();


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
	_weapon_enemy->Update(time);
	
	m_cameraHUD->update(time);
	m_camera->Update();

	UpdateGlobalVariable();
}

void ScenePlay::draw()
{
	m_background->draw();
	m_tree->draw();

	_weapon_enemy->Draw();
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

		for (int i = 0; i < objects.size(); i++)
		{
			CObject* ob = objects.at(i);

			switch (ob->_basic_type)
			{
			case Ground:
				_grounds.push_back(ob);
				break;
			case Enemy:
				if (ob->_enable)
					_enemies.push_back(ob);
				break;
			case Item:
				_items.push_back(ob);
				break;
			}
		}

		objects.clear();
	}
}

void ScenePlay::ProcessGroundsWithOneAnother()
{
	if (_grounds.size() > 0)
	{
		CollisionDirection collision_player1 = NoCollision;
		CollisionDirection collision_player2 = NoCollision;
		for (vector<CObject*>::iterator i = _grounds.begin(); i != _grounds.end(); i++)
		{
			CObject* ground = (*i);
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

			//Xét va chạm với các đối tượng k có trong quadtree
		}

		if (collision_player1 != TopCollision)
		{
			_player1->_physical.n = 0;
		}


	}
}

void ScenePlay::ProcessEnemiesWithOneAnother()
{
	if (_enemies.size() > 0)
	{
		for (vector<CObject*>::iterator i = _enemies.begin(); i != _enemies.end(); i++)
		{
			CObject* enemy = (*i);

			//Va chạm với người chơi 1

			//Va chạm với người chơi 2

			//Va chạm với đạn người chơi 1
			if (enemy->_hp > 0)
			{
				if (_weapon_player1->CheckCollision(enemy) != NoCollision && enemy->_can_impact)
				{
					enemy->_hp--;
				}
			}
			//Va chạm với đạn người chơi 2
			

		}
	}
}

void ScenePlay::ProcessItemsWithOneAnother()
{
	if (_items.size() > 0)
	{
		for (vector<CObject*>::iterator i = _items.begin(); i != _items.end(); i++)
		{
			CObject* item = (*i);

			//Xét va chạm với đạn
			if (item->_hp > 0)
			{
				if (_weapon_player1->CheckCollision(item) != NoCollision && item->_can_impact)
				{
					item->_hp--;
				}
			}

			//Xét va chạm với người chơi
			if (item->_hp == 0)
			{
			}

		}
	}
}

void ScenePlay::UpdateGlobalVariable()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	rs->_grounds = _grounds;
	rs->_weapon_enemy = _weapon_enemy;
}