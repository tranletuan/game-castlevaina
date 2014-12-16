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
	GetInstance()->m_life = 3;
	GetInstance()->m_numScore = 0;

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

	//high sorce map 1
	m_data = new CDatabase();
	m_highScore = m_data->readHighScore(PATH_HIGHSCORE_1);
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

	//Effect
	_effect_destroy = new CTexture(PATH_EFFECT_DESTROY, 3);
	_effect_shoot = new CTexture(PATH_EFFECT_SHOOT);
	_effect_die = new CTexture(PATH_EFFECT_DIE, 3);

	loadAllInMap();

}


void CResourcesManager::loadPlayAudio()
{

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

}

void CResourcesManager::unloadOverResource()
{

}

/* ------------------ Other -------------------*/
// load all texture object trong map
void CResourcesManager::loadAllInMap()
{
	string line;
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
					loadTexture(RESID_GROUND_EFFECT1);
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
				else if (line == "ItemFly")
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
					loadTexture(RESID_BOSS_1_BADGE);
					loadTexture(RESID_BOSS_1_BG);
				}
				else if (line == "BossGun")
				{
					loadTexture(RESID_BOSS_1_GUN);
				}
				else if (line == "GroundElectron")
				{
					loadTexture(RESID_GROUND_ELECTRON);
				}
				else if (line == "RunMan")
				{
					loadTexture(RESID_ENEMY_RUN_MAN);
				}
				else if (line == "StarEffect")
				{
					loadTexture(RESID_GROUND_STAR);
				}
				else if (line == "RockRoll")
				{
					loadTexture(RESID_ENEMY_ROCK_ROLL);
				}
				else if (line == "WaterFall")
				{
					loadTexture(RESID_GROUND_WATERFALL);
				}
				else if (line == "SniperBlock")
				{
					loadTexture(RESID_ENEMY_SNIPER_BLOCK);
				}
				else if (line == "BoomThrow")
				{
					loadTexture(RESID_ENEMY_BOOM_THROW);
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
	case RESID_ENEMY_SINPER_HIDE:
		_enemy_sniper_hide = new CTexture(PATH_ENEMY_SNIPER_HIDE, 4);
		break;
	case RESID_ENEMY_SINPER_STAND:
		_enemy_sniper_stand = new CTexture(PATH_ENEMY_SNIPER_STAND, 5);
		break;
	case RESID_ENEMY_WALL_TURRET:
		_enemy_wall_turret = new CTexture(PATH_ENEMY_WALL_TURRET, 3, 14);
		break;
	case RESID_ENEMY_BOOM_THROW:
		_enemy_boom_throw = new CTexture(PATH_ENEMY_BOOM_THROW, 4);
		break;
	case RESID_ENEMY_SNIPER_BLOCK:
		_enemy_sniper_block = new CTexture(PATH_ENEMY_SNIPER_BLOCK, 2);
		break;
	case RESID_GROUND_GRASS:
		_ground_grass = new CTexture(PATH_GROUND_GRASS);
		break;
	case RESID_GROUND_BRIDGE:
		_ground_auto_destroy_bridge = new CTexture(PATH_GROUND_AUTO_DETROY, 1, 6);
		break;
	case RESID_GROUND_EFFECT1:
		_ground_effect1 = new CTexture(PATH_GROUND_EFFECT1);
		break;
	case RESID_GROUND_ELECTRON:
		_ground_electron = new CTexture(PATH_GROUND_ELECTRON, 1, 2);
		break;
	case RESID_GROUND_STAR:
		_ground_star = new CTexture(PATH_GROUND_STAR, 6, 2);
		break;
	case RESID_GROUND_ROCK_FLY:
		_ground_rock_fly = new CTexture(PATH_GROUND_ROCK_FLY);
		break;
	case RESID_GROUND_WATER:
		_ground_water = new CTexture(PATH_GROUND_WATER);
		break;
	case RESID_GROUND_WATERFALL:
		_ground_waterfall = new CTexture(PATH_GROUND_WATETFALL, 2);
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
	case RESID_BOSS_1_BG:
		_boss1_bg = new CTexture(PATH_BOSS1_BG, 2);
		break;
	case RESID_BOSS_1_BADGE:
		_boss1_badge = new CTexture(PATH_BOSS1_BAGDE, 3);
		break;
	case RESID_BOSS_1_GUN:
		_boss_gun = new CTexture(PATH_BOSS_GUN, 3);
		break;
	default:
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



