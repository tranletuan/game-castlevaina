#include "world_test.h"

WorldTest::WorldTest(int cmd_show) : CGame(cmd_show)
{
	this->cmd_show = cmd_show;
	this->background = new CBackground(L"map1", 32);
	this->waepon = new CPlayerWaepon();
	this->bill = new CBill(123, Player1, D3DXVECTOR3(100, 190, 0));
	this->bill2 = new CBill(23, Player1, D3DXVECTOR3(50, 190, 0));
	this->map_reader = new CMapReader(L"map1");
	bill->_physical.vx = BILL_VX;
	bill2->_physical.vx = BILL_VX;

	test = 0;
}

WorldTest::~WorldTest()
{
	
}

void WorldTest::LoadResources(LPDIRECT3DDEVICE9 d3d_device)
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	bill->LoadResources();
	map_reader->LoadResources();
	_map_object = map_reader->GetListObject();
}

void WorldTest::RenderFrame(LPDIRECT3DDEVICE9 d3d_device)
{
	background->Draw();
	for (map<int, CObject*>::iterator i = _map_object.begin(); i != _map_object.end(); i++)
	{
		(*i).second->Draw();
	}

	bill->Draw();

	string show = to_string(bill->_physical.current_vy) + " : " + to_string(bill->_physical.current_vx) + 
		" : " + to_string(test) + " : " + to_string(bill->_physical.y);
	DisplayText(show);
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
	}
	else if (IsKeyDown(DIK_S))
	{
	}

} //Xử lý phím

void WorldTest::OnKeyDown(int key_code)
{
	switch (key_code)
	{
	case DIK_1:
		waepon->SetWaeponType(NBullet);
		break;
	case DIK_2:
		waepon->SetWaeponType(MBullet);
		break;
	case DIK_3:
		waepon->SetWaeponType(FBullet);
		break;
	case DIK_4:
		waepon->SetWaeponType(LBullet);
		break;
	case DIK_5:
		waepon->SetWaeponType(SBullet);
		break;
	case DIK_J:
		bill->SetStatus(Jump);
		bill->_physical.vy = 8.f;
		
		break;
	}
}

void WorldTest::OnKeyUp(int key_code)
{
	switch (key_code)
	{
	case DIK_D:
	case DIK_A:
		bill->Standing();
		break;

	case DIK_W:
	case DIK_S:
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
		cd = bill->_physical.Collision(&ground->_physical);
		
		//if (cd == TopCollision)
			test = cd;

		if (cd == TopCollision)
		{
			bill->_physical.n = GRAVITY;
			bill->_physical.y = ground->_physical.y + 33;
			bill->_physical.time_in_space = 0;
			 
			break;
		}
	}
	
	
	if (cd != TopCollision)
	{
		bill->_physical.n = 0;
		bill->_physical.ground = 0;
	}

	bill->Update(delta_time);

	if (bill->_physical.x < 0)
	{
		bill->_physical.x = 0;
		bill->_physical.vx = BILL_VX;
	}
	
	if (bill->_physical.x > kScreenWidth)
	{
		bill->_physical.vx = -BILL_VX;
	}

	//if (bill->_physical.vx > 0 )
	//camera->UpdateCamera(bill->_physical.x);
}