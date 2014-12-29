#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	// set var in class scene
	m_timeDuring = 1000;
	m_state = PS_InGame;
	_countScore = 20000;

	// out class scene
	m_background = new Background();
	m_cameraHUD = new CameraHUD();
	m_tree = new QTTree();
	m_listItemFLy = new CListItemFly();

	_weapon_player1 = new CPlayerWeapon();
	_player1 = new CBill();
	_player1->SetWeapon(_weapon_player1);
	_weapon_enemy = new CEnemyWeapon();
	_runmans = new CRunmanManager();
	
	init();
}

ScenePlay::~ScenePlay()
{

}

void ScenePlay::processInput()
{
	_player1->ProcessInput();
	m_camera->processInput();

	if (m_input->onKeyDown(DIK_RETURN))
	{
		m_nextScene = true;
	}
}

void ScenePlay::init()
{
	m_camera = m_resource->_camera;
	m_spDoor = new CSprite(m_resource->_boss3_door_die);
	m_spDoor->setPostion(D3DXVECTOR2(190, 98));

	switch (m_resource->m_curMap)
	{
	case 1:
		m_music_bg = m_resource->music_map1_bg;
		break;
	case 2:
		m_music_bg = m_resource->music_map2_bg;
		break;
	case 3:
		m_music_bg = m_resource->music_map3_bg;
		break;
	default:
		break;
	}

	m_audio->playSound(m_music_bg);
	m_audio->loopSound(m_music_bg);
}

void ScenePlay::update(float time)
{
	// xu ly trong scene
	if (m_state == PS_InGame)
	{
		// chuyen game over
		if (m_resource->m_life <= 0)
		{
			m_state = PS_GameOver;
			m_timeDuring = 80;
		}
		// chuyen next map
		if (_player1->_mission_complete)
		{
			m_state = PS_NextMap;
			m_timeDuring = 60;
		}
	}

	switch (m_state)
	{
	case PS_InGame:
		break;
	case PS_GameOver:
		m_state = PS_WaitNextScene;
		break;
	case PS_WaitNextScene:
		m_timeDuring--;
		if (m_timeDuring < 0)
		{
			m_nextScene = true;
		}
		break;
	case PS_Pause:
		break;
	case PS_NextMap:
		m_state = PS_WaitNextScene;
		break;
	default:
		break;
	}

	if (m_nextScene)
	{
		m_audio->stopSound(m_resource->sound_stage_clear);
		m_audio->stopSound(m_music_bg);
		m_state = PS_InGame;
		if (m_resource->m_life > 0)
		{
			// chuyen qua scene pause
			if (!_player1->_mission_complete)
			{
				SceneManager::getInstance()->createPauseScene();
			}
			// chuyen qua scene loading
			else
			{

				// thêm highscore mới vào
				m_resource->editHighScoreOfMap();

				if (m_resource->m_curMap == 1)
				{
					SceneManager::getInstance()->createWinScene();
				}
				else
				{
					SceneManager::getInstance()->createLoadingScene();
				}
			}

		}
		else
		{
			SceneManager::getInstance()->createOverScene();
		}
	}

	if (m_state != PS_InGame) return;

	// xu ly trong game
	UpdateFullListObjetcInView();
	ProcessGroundsWithOneAnother();
	ProcessEnemiesWithOneAnother();
	ProcessItemsWithOneAnother();

	m_background->update(time);
	m_tree->update(time);
	m_listItemFLy->Update(time);
	_player1->Update(time);
	_weapon_player1->Update(time);
	_weapon_enemy->Update(time);
	_runmans->Update(time);
	m_cameraHUD->update(time);
	m_camera->Update(time);

	if (_boss != NULL && _boss->_hp <= 0)
	{
		m_audio->stopSound(m_music_bg);
		m_audio->stopSound(m_resource->sound_boss_dead);
		_player1->GoingToNext();
	}

	UpdateGlobalVariable();
}

void ScenePlay::draw()
{
	m_background->draw();
	m_tree->draw();
	m_listItemFLy->Draw();
	_runmans->Draw();
	_weapon_enemy->Draw();
	_weapon_player1->Draw();
	_player1->Draw();
	if (m_resource->m_curMap == 3)
	{		
		if (_boss != NULL && _boss->_hp <= 0)
		{
			m_spDoor->Draw(m_spDoor->_pos);
		}
	}
	
	m_cameraHUD->draw();
	
}

void ScenePlay::destroy()
{

}

void ScenePlay::UpdateFullListObjetcInView()
{
	vector<CObject*> objects = m_resource->listObinView;

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
				{
					_enemies.push_back(ob);
					if (m_resource->m_curMap == 1)
					{
						if (ob->_specific_type == Boss1)
						{
							_boss = ob;
						}
					}
					else if (m_resource->m_curMap == 2)
					{
						if (ob->_specific_type == Boss2)
						{
							_boss = ob;
						}
					}
					else if (m_resource->m_curMap == 3)
					{
						if (ob->_specific_type == Boss3)
						{
							_boss = ob;
						}
					}
				}
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
		for (vector<CObject*>::iterator i = _grounds.begin(); i != _grounds.end(); i++)
		{
			CObject* ground = (*i);
			//Xét va chạm với người chơi 1
			if (_player1->GetIdGroundIgnore() != ground->_id && collision_player1 != TopCollision)
			{
				collision_player1 = _player1->CheckCollision(ground);

				if (collision_player1 == TopCollision && _player1->_physical.current_vy < 0)
				{
					_player1->Standing(ground->_physical.bounds.top, ground->_id);
					_player1->_physical.vx_accretion = 0;
					if (ground->_specific_type == Ground_Water)
					{
						_player1->SetEnviroment(Water);
					}
					else if (ground->_specific_type == Ground_Grass)
					{
						_player1->SetEnviroment(Land);
					}
					else if (ground->_specific_type == Ground_RockFly)
					{
						_player1->_physical.vx_accretion = ground->_physical.vx;
					}

				}
			}

			//Xét va chạm với những loại đạn có khả năng chạm đất
			_weapon_enemy->CheckCollisionWithGround(ground);
		}

		//Xét va chạm với các đối tượng k có trong quadtree
		_runmans->CheckCollisionWithGround();

		if (collision_player1 != TopCollision)
		{
			_player1->_physical.n = 0;
		}


	}
}

void ScenePlay::ProcessEnemiesWithOneAnother()
{
	//Quái nằm trong quadtree
	if (_enemies.size() > 0)
	{
		for (vector<CObject*>::iterator i = _enemies.begin(); i != _enemies.end(); i++)
		{
			CObject* enemy = (*i);

			//Va chạm với người chơi 1
			if (_player1->_can_impact && enemy->_specific_type != Wall_Turret && enemy->_specific_type != Ground_Canon)
			{
				if (_player1->CheckCollision(enemy) != NoCollision && _player1->_can_impact)
				{
					_player1->Dying();
				}
			}

			//Va chạm với đạn người chơi 1
			if (enemy->_hp > 0)
			{
				if (_weapon_player1->CheckCollision(enemy) != NoCollision && enemy->_can_impact)
				{
					// xử lý điểm + thêm 1 mạng
					m_resource->m_numScore += 500;
					_countScore -= 500;

					if (_countScore < 0)
					{
						_countScore = 20000;
						m_resource->m_life++;
						m_resource->sound_bill_1up->Reset();
						m_audio->playSound(m_resource->sound_bill_1up);
					}

					enemy->_hp--;

					// chơi sound
					if (enemy->_hp > 0)
					{
						m_resource->sound_enemy_attacked->Reset();
						m_audio->playSound(m_resource->sound_enemy_attacked);
					}
				}
			}
			//Va chạm với đạn người chơi 2
			//Boss chết thì tất cả enemy đều chết
			if (_boss != NULL && _boss->_hp <= 0)
			{
				enemy->_hp = 0;
			}
		}
	}

	//Quái nằm ngoài quadtree
	_runmans->CheckCollisionWithPlayer(_weapon_player1, _player1);

	//Xét va chạm đạn của quái với người chơi
	_weapon_enemy->CheckCollisionWithPlayer(_player1);

	//Xét va chạm đạn của quái với đạn của người chơi
	_weapon_enemy->CheckCollisionWithWeaponPlayer(_weapon_player1);

	//boss chết thì vô hiệu hóa tất cả các loại đạn của quái
	if (_boss != NULL && _boss->_hp <= 0)
	{
		_weapon_enemy->DestroyAllBullet();
	}
}

void ScenePlay::ProcessItemsWithOneAnother()
{
	//List Item Trong Quadtree
	if (_items.size() > 0)
	{
		for (vector<CObject*>::iterator i = _items.begin(); i != _items.end(); i++)
		{
			CObject* item = (*i);

			//Xét va chạm với người chơi 1
			if (item->_hp == 0 && item->_enable)
			{
				if (_player1->_physical.Collision(&item->_physical) != NoCollision)
				{
					// play sound
					m_resource->sound_get_item->Reset();
					m_audio->playSound(m_resource->sound_get_item);

					switch (item->_specific_type)
					{
					case ItemM_Stand:						
						_weapon_player1->SetWaeponType(WPM);
						break;
					case ItemF_Stand:					
						_weapon_player1->SetWaeponType(WPF);
						break;
					case ItemS_Stand:						
						_weapon_player1->SetWaeponType(WPS);
						break;
					case ItemL_Stand:						
						_weapon_player1->SetWaeponType(WPL);
						break;
					case ItemB_Stand:
						_player1->Undying();
						break;

					}

					item->_physical.SetBounds(0, 0, 0, 0);
					item->_enable = false;
				}
			}

			//Xét va chạm với đạn người chơi 1
			if (item->_hp > 0)
			{
				if (_weapon_player1->CheckCollision(item) != NoCollision && item->_can_impact)
				{
					item->_hp--;
				}
			}
		}
	}

	//List Item Ngoài Quadtree
	m_listItemFLy->CheckCollisionWithPlayerAndWeapon(_weapon_player1, _player1);

}

void ScenePlay::UpdateGlobalVariable()
{
	m_resource->_grounds = _grounds;
	m_resource->_weapon_enemy = _weapon_enemy;
}