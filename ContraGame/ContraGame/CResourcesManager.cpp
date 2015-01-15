#include "CResourcesManager.h"

CResourcesManager* CResourcesManager::m_resource = NULL;

CResourcesManager* CResourcesManager::GetInstance()
{
	if (m_resource == NULL)
	{
		m_resource = new CResourcesManager();
	}
	return m_resource;
}

void CResourcesManager::prepareManager(LPD3DXSPRITE sp, LPDIRECT3DDEVICE9 pd3Device, HINSTANCE Hinst, HWND wndHandle,
	CInput *input, CAudio *audio)
{
	kHInstance = Hinst;
	kDevice = pd3Device;
	kHWND = wndHandle;
	GetInstance()->m_input = input;
	kSpriteHandler = sp;
	GetInstance()->m_audio = audio;

	// init var default
	GetInstance()->m_life = 5;
	GetInstance()->m_numScore = 0;
	GetInstance()->m_highScore = 0;
	GetInstance()->m_numScore = 0;
	GetInstance()->m_effecKill = 0;
	GetInstance()->readFileConfiDefault();
	GetInstance()->m_numBullet = 1;
}


CResourcesManager::CResourcesManager()
{

}

CResourcesManager::~CResourcesManager()
{
}

/* -------------- Menu Scene -------------*/
void CResourcesManager::loadMenuResource()
{
	loadMenuAudio();
	loadMenuGraphics();
}

void CResourcesManager::loadMenuGraphics()
{

	menu_bg = new CTexture(PATH_MENU_BG, D3DCOLOR_XRGB(0, 0, 0));
	menu_badge = new  CTexture(PATH_MENU_BADGE, D3DCOLOR_XRGB(0, 0, 0));
	menu_item1 = new CTexture(PATH_MENU_ITEM1, D3DCOLOR_XRGB(0, 0, 0));
	menu_item2 = new CTexture(PATH_MENU_ITEM2, D3DCOLOR_XRGB(0, 0, 0));

}

void CResourcesManager::loadMenuAudio()
{
	music_menu_bg = m_audio->LoadSound(PATH_MUSIC_MENU_BG);
}


void CResourcesManager::unloadMenuResource()
{

}

/* -------------- Loading Scene -------------*/
void CResourcesManager::loadLoadingResource()
{
	loadLoadingGraphics();
	loadLoadingAudio();
}

void CResourcesManager::loadLoadingGraphics()
{
	load_1p = new CTexture(PATH_LOAD_1P, D3DCOLOR_XRGB(0, 0, 0));
	load_rest = new CTexture(PATH_LOAD_REST, D3DCOLOR_XRGB(0, 0, 0));
	load_hi = new CTexture(PATH_LOAD_HI, D3DCOLOR_XRGB(0, 0, 0));
	load_stage1 = new CTexture(PATH_LOAD_STAGE1, D3DCOLOR_XRGB(0, 0, 0));
	load_nameStage1 = new CTexture(PATH_LOAD_NAMESTAGE1, D3DCOLOR_XRGB(0, 0, 0));
	load_stage2 = new CTexture(PATH_LOAD_STAGE2, D3DCOLOR_XRGB(0, 0, 0));
	load_nameStage2 = new CTexture(PATH_LOAD_NAMESTAGE2, D3DCOLOR_XRGB(0, 0, 0));
	load_stage3 = new CTexture(PATH_LOAD_STAGE3, D3DCOLOR_XRGB(0, 0, 0));
	load_nameStage3 = new CTexture(PATH_LOAD_NAMESTAGE3, D3DCOLOR_XRGB(0, 0, 0));
	load_number = new CTexture(PATH_LOAD_NUMBER, 10);



	//load high sorce map
	m_data = new CDatabase();

}

void CResourcesManager::loadLoadingAudio()
{

}

void CResourcesManager::unloadLoadingResource()
{

}


/* -------------- Play Scene -------------*/
void CResourcesManager::loadPlayResource()
{
	loadPlayGraphics();
	loadPlayAudio();
}

void CResourcesManager::loadPlayGraphics()
{
	// Camera HUD
	HUD_badge = new CTexture(PATH_HUD_BADGE); // huy chuong
	HUD_gameover = new CTexture(PATH_HUD_GAMEOVER); //Game over
	HUD_effect_kill = new CTexture(PATH_HUD_EFFECT_KILL, 3); //Game over

	//Player
	_bill_stand = new CTexture(PATH_PLAYER_STAND, 6);
	_bill_jump = new CTexture(PATH_PLAYER_JUMP, 4);
	_bill_die = new CTexture(PATH_PLAYER_DIE, 5);
	_bill_move = new CTexture(PATH_PLAYER_MOVE, 5, 4);
	_bill_in_water = new CTexture(PATH_PLAYER_IN_WATER, 10);


	//Bullet
	_bullet_n = new CTexture(PATH_BULLET_N);
	_bullet_s = new CTexture(PATH_BULLET_S, 3);
	_bullet_l = new CTexture(PATH_BULLET_L);
	_bullet_f = new CTexture(PATH_BULLET_F);
	_bullet_m = new CTexture(PATH_BULLET_M);
	_bullet_ne = new CTexture(PATH_BULLET_NE);
	_bullet_b = new CTexture(PATH_BULLET_B);
	_bullet_b2 = new CTexture(PATH_BULLET_B2, 4);
	_bullet_b3 = new CTexture(PATH_BULLET_B3, 3);
	_bullet_sp = new CTexture(PATH_BULLET_SP);

	//Effect
	_effect_destroy = new CTexture(PATH_EFFECT_DESTROY, 3);
	_effect_shoot = new CTexture(PATH_EFFECT_SHOOT);
	_effect_die = new CTexture(PATH_EFFECT_DIE, 3);

	_boss3_door_die = new CTexture(PATH_BOSS3_DOOR_DIE);
}

void CResourcesManager::loadPlayAudio()
{
	music_map1_bg = m_audio->LoadSound(PATH_MUSIC_MAP1_BG);
	music_map2_bg = m_audio->LoadSound(PATH_MUSIC_MAP2_BG);
	music_map3_bg = m_audio->LoadSound(PATH_MUSIC_MAP3_BG);


	sound_enemy_attacked = m_audio->LoadSound(PATH_SOUND_ENEMY_ATTACKED);
	sound_bill_1up = m_audio->LoadSound(PATH_SOUND_BILL_1UP);
	sound_bill_dead = m_audio->LoadSound(PATH_SOUND_BILL_DEAD);
	sound_boss_dead = m_audio->LoadSound(PATH_SOUND_BOSS_DEAD);
	sound_stage_clear = m_audio->LoadSound(PATH_SOUND_STAGE_CLEAR);
	sound_get_item = m_audio->LoadSound(PATH_SOUND_GET_ITEM);
	sound_bullet_default = m_audio->LoadSound(PATH_SOUND_BULLET_DEFALUT);
	sound_bullet_m = m_audio->LoadSound(PATH_SOUND_BULLET_M);
	sound_bullet_s = m_audio->LoadSound(PATH_SOUND_BULLET_S);
	sound_bullet_l = m_audio->LoadSound(PATH_SOUND_BULLET_L);

}

void CResourcesManager::unloadPlayResource()
{

}

/*-----------  Pause ----------------- */
void CResourcesManager::loadPauseResource()
{
	loadPauseGraphics();
	loadPauseAudio();
}

void CResourcesManager::loadPauseGraphics()
{
	pause_title = new CTexture(PATH_PAUSE_TITLE);
	pause_continue = new CTexture(PATH_PAUSE_CONTINUE);
	pause_end = new CTexture(PATH_PAUSE_END);
}

void CResourcesManager::loadPauseAudio()
{

}

void CResourcesManager::unloadPauseResource()
{

}

/*----------- Game Over ----------*/
void CResourcesManager::loadOverResource()
{
	loadOverGraphics();
	loadOverAudio();
}

void CResourcesManager::loadOverGraphics()
{
	over_title = new CTexture(PATH_OVER_TITLE);
}

void CResourcesManager::loadOverAudio()
{
	music_gameover_bg = m_audio->LoadSound(PATH_MUSIC_GAMEOVER_BG);
}

void CResourcesManager::unloadOverResource()
{

}

/*----------- Win Gamer----------*/

void CResourcesManager::loadWinResource()
{
	loadWinGraphics();
	loadWinAudio();
}

void CResourcesManager::loadWinGraphics()
{
	win_congra = new CTexture(PATH_WIN_CONGRU);
	win_victory = new CTexture(PATH_WIN_VICTORY);
	win_lead = new CTexture(PATH_WIN_LEAD);
	win_thay = new CTexture(PATH_WIN_THAY);
	win_product = new CTexture(PATH_WIN_PRODUCT);
	win_tien = new CTexture(PATH_WIN_TIEN);
	win_tuan = new CTexture(PATH_WIN_TUAN);
	win_copy = new CTexture(PATH_WIN_COPY);
}

void CResourcesManager::loadWinAudio()
{
	music_win_bg = m_audio->LoadSound(PATH_MUSIC_WIN_BG);
}

void CResourcesManager::unloadWinResource()
{

}

/* ------------------ Other -------------------*/
// load all texture object trong map
void CResourcesManager::loadAllInMap()
{

	string path = "";
	switch (m_nextMap)
	{
	case 1:
		path = PATH_CONFI_MAP_1;
		/* --- Background ---*/
		background = new CTexture(PATH_MAP_BG1_PIC, D3DCOLOR_XRGB(0, 0, 0));
		map_bg_listTile = loadFileTextBG(PATH_MAP_BG1_TEXT);
		// load object from file text
		map_listOb = loadFileTextOB(PATH_OB_MAP1_QT);
		// load list ob khong nam trong quad tree
		listObNoTree = loadFileTextOBNoneTree(PATH_OB_MAP1);
		// load quadtree
		map_listNode = loadFileTextNode(PATH_QT_MAP1);
		break;
	case 2:
		path = PATH_CONFI_MAP_2;
		/* --- Background ---*/
		background = new CTexture(PATH_MAP_BG2_PIC, D3DCOLOR_XRGB(0, 0, 0));
		map_bg_listTile = loadFileTextBG(PATH_MAP_BG2_TEXT);
		// load object from file text
		map_listOb = loadFileTextOB(PATH_OB_MAP2_QT);
		// load list ob khong nam trong quad tree
		listObNoTree = loadFileTextOBNoneTree(PATH_OB_MAP2);
		// load quadtree
		map_listNode = loadFileTextNode(PATH_QT_MAP2);
		break;
	case 3:
		path = PATH_CONFI_MAP_3;
		/* --- Background ---*/
		background = new CTexture(PATH_MAP_BG3_PIC, D3DCOLOR_XRGB(0, 0, 0));
		map_bg_listTile = loadFileTextBG(PATH_MAP_BG3_TEXT);
		// load object from file text
		map_listOb = loadFileTextOB(PATH_OB_MAP3_QT);
		// load list ob khong nam trong quad tree
		listObNoTree = loadFileTextOBNoneTree(PATH_OB_MAP3);
		// load quadtree
		map_listNode = loadFileTextNode(PATH_QT_MAP3);
		break;
	default:
		break;
	}

	// load camera + bill
	float posX = map_listOb.at(map_listOb.size() - 2)->getPosX();
	float posY = map_listOb.at(map_listOb.size() - 2)->getPosY();
	_camera = new CCamera(posX, posY);

	posX = map_listOb.at(map_listOb.size() - 1)->getPosX();
	posY = map_listOb.at(map_listOb.size() - 1)->getPosY();
	m_posBill = D3DXVECTOR3(posX, posY, 0);

	// xoa 2 ob cuoi cua list	
	map_listOb.erase(map_listOb.end() - 2, map_listOb.end());

	// xoa list load tu file confi
	if (_listString.size() > 0)
	{
		_listString.erase(_listString.begin(), _listString.end());
	}

	// load all texture
	ifstream myfile(path);
	string line = "";
	int dem = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (dem == 0)
			{
				m_curMap = m_nextMap;
				m_nextMap = atoi(line.c_str());
				dem++;
			}
			else
			{
				// vo list string
				_listString.push_back(line);
				// load texture
				if (line == "Ground")
				{
					loadTexture(RESID_GROUND_GRASS);
				}
				else if (line == "Sniper")
				{
					loadTexture(RESID_ENEMY_SINPER_STAND);
				}
				else if (line == "WaterEffect1")
				{
					loadTexture(RESID_EFFECT_WATER);
				}
				else if (line == "Water")
				{
					loadTexture(RESID_GROUND_WATER);
				}
				else if (line == "Brigde")
				{
					loadTexture(RESID_GROUND_BRIDGE);
				}
				else if (line == "SniperHide")
				{
					loadTexture(RESID_ENEMY_SINPER_HIDE);
				}
				else if (line == "Item")
				{
					loadTexture(RESID_ITEM_FLY);
				}
				else if (line == "ItemStand")
				{
					loadTexture(RESID_ITEM_STAND);
				}
				else if (line == "BlockHouse")
				{
					loadTexture(RESID_ENEMY_WALL_TURRET);
				}
				else if (line == "Obstacle")
				{
					loadTexture(RESID_ENEMY_GROUND_CANNON);
				}
				else if (line == "Boss1")
				{
					loadTexture(RESID_BOSS_1);
				}
				else if (line == "Boss2")
				{
					loadTexture(RESID_BOSS_2);
				}
				else if (line == "GroundElectron")
				{
					loadTexture(RESID_GROUND_ELECTRON);
				}
				else if (line == "RunMan")
				{
					loadTexture(RESID_ENEMY_RUN_MAN);
					loadTexture(RESID_ENEMY_RUN_MAN_FIRE);
				}
				else if (line == "StarEffect")
				{
					loadTexture(RESID_EFFECT_STAR);
				}
				else if (line == "RockRoll")
				{
					loadTexture(RESID_ENEMY_ROCK_ROLL);
				}
				else if (line == "RockFly")
				{
					loadTexture(RESID_GROUND_ROCK_FLY);
				}
				else if (line == "SniperBoss")
				{
					loadTexture(RESID_ENEMY_SNIPER_BOSS);
				}
				else if (line == "WaterFall")
				{
					loadTexture(RESID_EFFECT_WATERFALL);
				}
				else if (line == "SniperBlock")
				{
					loadTexture(RESID_ENEMY_SNIPER_BLOCK);
				}
				else if (line == "Boom")
				{
					loadTexture(RESID_ENEMY_BOOM_THROW);
				}
				else if (line == "Fire")
				{
					loadTexture(RESID_ENEMY_FIRE);
				}
				else if (line == "ItemStand")
				{
					loadTexture(RESID_ITEM_STAND);
				}
				else if (line == "Tank")
				{
					loadTexture(RESID_ENEMY_TANK);
				}
				else if (line == "SniperWater")
				{
					loadTexture(RESID_ENEMY_SNIPER_WATER);
				}
				else if (line == "Boss3")
				{
					loadTexture(RESID_BOSS_3);
				}
			}
		}
		myfile.close();
	}
}

// unload all texture object trong map
void CResourcesManager::unloadAllInMap()
{

}

// load tung ctexture 
void CResourcesManager::loadTexture(ResourceID id)
{
	switch (id)
	{
	case RESID_BG1:
		background = new CTexture(PATH_MAP_BG1_PIC, D3DCOLOR_XRGB(0, 0, 0));
		break;
	case RESID_BG2:
		background = new CTexture(PATH_MAP_BG2_PIC, D3DCOLOR_XRGB(0, 0, 0));
		break;
	case RESID_BG3:
		break;
	case RESID_BILL_DIE:
		_bill_die = new CTexture(PATH_PLAYER_DIE, 5);
		break;
	case RESID_BILL_IN_WATER:
		_bill_in_water = new CTexture(PATH_PLAYER_IN_WATER, 10);
		break;
	case RESID_BILL_JUMP:
		_bill_jump = new CTexture(PATH_PLAYER_JUMP, 4);
		break;
	case RESID_BILL_MOVE:
		_bill_move = new CTexture(PATH_PLAYER_MOVE, 5, 4);
		break;
	case RESID_BILL_STAND:
		_bill_stand = new CTexture(PATH_PLAYER_STAND, 6);
		break;
	case RESID_ITEM_FLY:
		_item = new CTexture(PATH_ITEM, 10);
		break;
	case RESID_ITEM_STAND:
		_item_stand = new CTexture(PATH_ITEM_STAND, 10);
		break;
	case RESID_ENEMY_FIRE:
		_enemy_fire = new CTexture(PATH_ENEMY_FIRE, 3);
		break;
	case RESID_ENEMY_GROUND_CANNON:
		_enemy_ground_canon = new CTexture(PATH_ENEMY_GROUND_CANON, 3, 5);
		break;
	case RESID_ENEMY_ROCK_ROLL:
		_enemy_rock_roll = new CTexture(PATH_ENEMY_ROCK_ROLL, 5);
		break;
	case RESID_ENEMY_RUN_MAN:
		_enemy_run_man = new CTexture(PATH_ENEMY_RUN_MAN, 8);
		break;
	case RESID_ENEMY_RUN_MAN_FIRE:
		_enemy_run_man_fire = new CTexture(PATH_ENEMY_RUN_MAN_FIRE, 2);
		break;
	case RESID_ENEMY_SINPER_HIDE:
		_enemy_sniper_hide = new CTexture(PATH_ENEMY_SNIPER_HIDE, 4);
		break;
	case RESID_ENEMY_SINPER_STAND:
		_enemy_sniper_stand = new CTexture(PATH_ENEMY_SNIPER_STAND, 5);
		break;
	case RESID_ENEMY_WALL_TURRET:
		_enemy_wall_turret = new CTexture(PATH_ENEMY_WALL_TURRET, 3, 14);
		break;
	case RESID_ENEMY_SNIPER_BOSS:
		_enemy_sniper_boss = new CTexture(PATH_ENEMY_SNIPER_BOSS, 7);
		break;
	case RESID_ENEMY_BOOM_THROW:
		_enemy_boom_throw = new CTexture(PATH_ENEMY_BOOM_THROW, 4);
		break;
	case RESID_ENEMY_SNIPER_BLOCK:
		_enemy_sniper_block = new CTexture(PATH_ENEMY_SNIPER_BLOCK, 2);
		break;
	case RESID_ENEMY_TANK:
		_enemy_tank = new CTexture(PATH_ENEMY_TANK, 6, 3);
		break;
	case RESID_ENEMY_SNIPER_WATER:
		_enemy_sniper_water = new CTexture(PATH_ENEMY_SNIPER_WATER, 3);
		break;
	case RESID_GROUND_GRASS:
		_ground_grass = new CTexture(PATH_GROUND_GRASS);
		break;
	case RESID_GROUND_BRIDGE:
		_ground_auto_destroy_bridge = new CTexture(PATH_GROUND_AUTO_DETROY, 1, 6);
		break;
	case RESID_EFFECT_WATER:
		_effect_water = new CTexture(PATH_EFFECT_WATER);
		break;
	case RESID_GROUND_ELECTRON:
		_ground_electron = new CTexture(PATH_GROUND_ELECTRON, 1, 2);
		break;
	case RESID_EFFECT_STAR:
		_effect_star = new CTexture(PATH_EFFECT_STAR, 6, 2);
		break;
	case RESID_GROUND_ROCK_FLY:
		_ground_rock_fly = new CTexture(PATH_GROUND_ROCK_FLY);
		break;
	case RESID_GROUND_WATER:
		_ground_water = new CTexture(PATH_GROUND_WATER);
		break;
	case RESID_EFFECT_WATERFALL:
		_effect_waterfall = new CTexture(PATH_EFFECT_WATETFALL, 2);
		break;
	case RESID_EFFECT_DESTROY:
		_effect_destroy = new CTexture(PATH_EFFECT_DESTROY, 3);
		break;
	case RESID_EFFECT_DIE:
		_effect_die = new CTexture(PATH_EFFECT_DIE, 3);
		break;
	case RESID_EFFECT_SHOOT:
		_effect_shoot = new CTexture(PATH_EFFECT_SHOOT);
		break;
	case REDID_BULLET_B:
		_bullet_b = new CTexture(PATH_BULLET_B);
		break;
	case REDID_BULLET_F:
		_bullet_f = new CTexture(PATH_BULLET_F);
		break;
	case REDID_BULLET_L:
		_bullet_l = new CTexture(PATH_BULLET_L);
		break;
	case REDID_BULLET_M:
		_bullet_m = new CTexture(PATH_BULLET_M);
		break;
	case REDID_BULLET_N:
		_bullet_n = new CTexture(PATH_BULLET_N);
		break;
	case REDID_BULLET_NE:
		_bullet_ne = new CTexture(PATH_BULLET_NE);
		break;
	case REDID_BULLET_S:
		_bullet_s = new CTexture(PATH_BULLET_S, 3);
		break;
	case RESID_BOSS_1:
		_boss1_bg = new CTexture(PATH_BOSS1_BG, 2);
		_boss1_badge = new CTexture(PATH_BOSS1_BAGDE, 3);
		_boss1_gun = new CTexture(PATH_BOSS1_GUN, 3);
		break;
	case RESID_BOSS_2:
		_boss2_elbow = new CTexture(PATH_BOSS2_ELBOW);
		_boss2_hand = new CTexture(PATH_BOSS2_HAND);
		_boss2_live = new CTexture(PATH_BOSS2_LIVE, 3, 4);
		_boss2_die = new CTexture(PATH_BOSS2_DIE);
		break;
	case RESID_BOSS_3:
		_boss3 = new CTexture(PATH_BOSS3, 2, 6);
		break;
	}
}

// get tung ctexture
CTexture* CResourcesManager::getTexture(ResourceID id)
{
	CTexture* x = new CTexture();
	return x;
}

vector<CObject*> CResourcesManager::loadFileTextOBNoneTree(string path)
{
	vector<CObject*> gameOb;
	string line;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			CObject *ob = splitTextPushOB(line);
			gameOb.push_back(ob);
		}
		myfile.close();
	}
	return gameOb;
}

vector<int> CResourcesManager::loadFileTextBG(string path)
{
	vector<int> x;
	ifstream in(path, ios::in);
	int number;
	while (in >> number)
	{
		x.push_back(number);
	}

	in.close();
	return x;
}

vector<QTNode*> CResourcesManager::loadFileTextNode(string path)
{
	vector<QTNode*> listNode;
	string line;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			QTNode *ob = splitTextPushNode(line);
			listNode.push_back(ob);
		}
		myfile.close();
	}
	return listNode;
}

vector<CObject*> CResourcesManager::loadFileTextOB(string path)
{
	vector<CObject*> gameOb;
	string line;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			CObject *ob = splitTextPushOB(line);
			gameOb.push_back(ob);
		}
		myfile.close();
	}
	return gameOb;
}

CObject* CResourcesManager::splitTextPushOB(string str)
{
	CObject* ob = new CObject();
	string delimiter = " ";
	int dem = 0;
	size_t pos = 0;
	std::string token;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		if (dem == 0)
		{
			ob->setID(atoi(token.c_str()));
		}
		else if (dem == 1)
		{
			ob->setSpecificType(token);
		}
		else if (dem == 2)
		{
			ob->setPosX((float)atoi(token.c_str()));
		}
		else if (dem == 3)
		{
			ob->setPosY((float)atoi(token.c_str()));
		}
		else if (dem == 4)
		{
			ob->setWidth(atoi(token.c_str()));
		}
		else if (dem == 5)
		{
			ob->setHeight(atoi(token.c_str()));
		}
		else if (dem == 6) // doi voi cac ob nam ngoai quad tree co huong
		{
			ob->setTrack(token);
		}
		str.erase(0, pos + delimiter.length());
		dem++;
	}

	return ob;
}

QTNode* CResourcesManager::splitTextPushNode(string str)
{
	QTNode* node = new QTNode();
	string delimiter = " ";
	int dem = 0;
	size_t pos = 0;
	std::string token;
	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		token = str.substr(0, pos);
		if (dem == 0)
		{
			node->setID(token);
			int lv = token.length() / 2;
			node->setLevel(lv);
		}
		else if (dem == 1)
		{
			node->setPosX((float)atoi(token.c_str()));
		}
		else if (dem == 2)
		{
			node->setPosY((float)atoi(token.c_str()));
		}
		else if (dem == 3)
		{
			node->setWidth(atoi(token.c_str()));
		}
		else if (dem == 4)
		{
			node->setHeight(atoi(token.c_str()));
		}
		else if (dem == 5)
		{
			// truong hop co list object o node la			
			token.erase(pos, pos + delimiter.length());
			node->setListOb(token);
		}

		str.erase(0, pos + delimiter.length());
		dem++;
	}

	return node;
}

void CResourcesManager::readFileConfiDefault()
{
	// doc map next 
	string line;
	ifstream myfile(PATH_CONFI_DEFAULT);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			GetInstance()->m_nextMap = atoi(line.c_str());
		}
		myfile.close();
	}
	GetInstance()->m_curMap = GetInstance()->m_nextMap;
}

void CResourcesManager::editHighScoreOfMap()
{
	if (CResourcesManager::GetInstance()->m_numScore > CResourcesManager::GetInstance()->m_highScore)
	{
		switch (m_curMap)
		{
		case 1:
			m_data->writeHighScore(PATH_HIGHSCORE_1, m_numScore);
			break;
		case 2:
			m_data->writeHighScore(PATH_HIGHSCORE_2, m_numScore);
			break;
		case 3:
			m_data->writeHighScore(PATH_HIGHSCORE_3, m_numScore);
			break;
		default:
			break;
		}

	}
}

void CResourcesManager::readHighScoreOfMap()
{
	switch (m_nextMap)
	{
	case 1:
		m_highScore = m_data->readHighScore(PATH_HIGHSCORE_1);
		break;
	case 2:
		m_highScore = m_data->readHighScore(PATH_HIGHSCORE_2);
		break;
	case 3:
		m_highScore = m_data->readHighScore(PATH_HIGHSCORE_3);
		break;
	default:
		break;
	}
}