#include "world_test.h"

WorldTest::WorldTest(int cmd_show) : CGame(cmd_show)
{
	this->cmd_show = cmd_show;
	this->background = new CBackground(L"map1", 32);
	this->waepon = new CPlayerWaepon();
	this->bill = new CBill(123, Player1, D3DXVECTOR3(64, 190, 0), 32, 32);
	this->bill2 = new CBill(23, Player1, D3DXVECTOR3(50, 190, 0), 32, 32);
	this->map_reader = new CMapReader(L"map1");
	this->bullet = new CFBullet(10);
	
	test = 0;
}

WorldTest::~WorldTest()
{
	
}

void WorldTest::LoadResources(LPDIRECT3DDEVICE9 d3d_device)
{

	CResourcesManager* rs = CResourcesManager::GetInstance();
	
	waepon->LoadResources();
	bill->LoadResources();
	bullet->LoadResources();
	map_reader->LoadResources();
	_map_object = map_reader->GetListObject();
	background->LoadResources();
}

void WorldTest::RenderFrame(LPDIRECT3DDEVICE9 d3d_device)
{
	//background->Draw();
	for (map<int, CObject*>::iterator i = _map_object.begin(); i != _map_object.end(); i++)
	{
		(*i).second->Draw();
	}


	bill->Draw();
	waepon->Draw();
	bullet->Draw();
	
}

void WorldTest::ProcessInput(LPDIRECT3DDEVICE9 d3d_device, int delta)
{
	//Set phím di chuyển trái phải
	if (IsKeyDown(DIK_D))
	{
		bill->Moving(BILL_VX);
	}
	else if (IsKeyDown(DIK_A))
	{
		bill->Moving(-BILL_VX);
	}

	//Set phím hướng súng
	if (IsKeyDown(DIK_W))
	{
		bill->SetGunDirection(Up);
	}
	else if (IsKeyDown(DIK_S))
	{
		bill->SetGunDirection(Down);
	}

} //Xử lý phím

void WorldTest::OnKeyDown(int key_code)
{
	switch (key_code)
	{
	case DIK_1:
		waepon->SetWaeponType(WPN);
		bill->Dying();
		break;
	case DIK_2:
		waepon->SetWaeponType(WPM);
		break;
	case DIK_3:
		waepon->SetWaeponType(WPF);
		break;
	case DIK_4:
		waepon->SetWaeponType(WPL);
		break;
	case DIK_5:
		waepon->SetWaeponType(WPS);
		break;
	case DIK_J:
		if (bill->GetGunDirection() != Down)
			bill->Jumping();
		else
		{
			for (map<int, CObject*>::iterator i = _map_object.begin(); i != _map_object.end(); i++)
			{
				CObject* ground = (*i).second;
				if (bill->Falling(ground) == true) return;
			}
		}
		break;
	case DIK_L:
		bill->Attacking(waepon);
		break;
	}
}

void WorldTest::OnKeyUp(int key_code)
{
	switch (key_code)
	{
	case DIK_D:
	case DIK_A:
		bill->Moving(0);
		
		break;

	case DIK_W:
	case DIK_S:
		bill->SetGunDirection(Normal);
		break;
	case DIK_J:
		
		break;
	}
	
}

void WorldTest::GameUpdate(int delta_time)
{
	CCamera* camera = CResourcesManager::GetInstance()->_camera;

	CollisionDirection cd = Undefined;
	for (map<int, CObject*>::iterator i = _map_object.begin(); i != _map_object.end(); i++)
	{
		CObject* ground = (*i).second;

		//Trường hợp rơi xuống
		if (bill->GetIdGroundIgnore() != ground->_id)
		{
			cd = bill->_physical.Collision(&ground->_physical);
			if (cd == TopCollision && bill->_physical.current_vy < 0)
			{
				bill->Standing(ground->_physical.bounds.top + BILL_BOUNDS_HEIGHT / 2 + 1, ground->_id);

				if (ground->_specific_type == Ground2)
				{
					bill->SetEnviroment(Water);
				}
				else
				{
					bill->SetEnviroment(Land);
				}
				break;
			}
		}
	}
	
	if (cd != TopCollision)
	{
		bill->_physical.n = 0;
	}

	bill->Update(delta_time);
	waepon->Update(delta_time);
	bullet->Update(delta_time);
	camera->UpdateCamera(bill->_physical.x);
}

