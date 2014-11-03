#include "world_test.h"

WorldTest::WorldTest(int cmd_show) : CGame(cmd_show)
{
	this->cmd_show = cmd_show;
	this->background = new CBackground(L"map1", 32);
	this->bill = new CBill(D3DXVECTOR3(20, 140, 0), 34);
	this->bill2 = new CBill(D3DXVECTOR3(100, 140, 0), 34);
	this->waepon = new CPlayerWaepon();
	this->ground = new CAutoDestroyBridge(GroundBridge, D3DXVECTOR3(100, 16, 0));
	test = 0;
}

WorldTest::~WorldTest()
{
	
}

void WorldTest::LoadResources(LPDIRECT3DDEVICE9 d3d_device)
{
	CResourcesManager* rs = CResourcesManager::GetInstance();

	background->LoadResources();
	bill->LoadResources();
	bill2->LoadResources();
	ground->LoadResources();
}

void WorldTest::RenderFrame(LPDIRECT3DDEVICE9 d3d_device)
{
	background->Draw();
	bill->Draw();
	bill2->Draw();
	waepon->Draw();
	ground->Draw();
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
		waepon->SetWaeponType(NBullet);
		ground->SetTarget(100);
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
		D3DXVECTOR3 pos = D3DXVECTOR3(bill->_physical.x, bill->_physical.y, 0);
		waepon->Shooting(pos, test, bill->_physical.vx);
		test += 30;
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
		bill->SetGunDirection(Normal);
		break;
	}
	
}

void WorldTest::GameUpdate(int delta_time)
{
	CCamera* camera = CResourcesManager::GetInstance()->_camera;
	
	bill->Update(delta_time);
	bill2->Update(delta_time);
	waepon->Update(delta_time);
	
	camera->UpdateCamera(bill->_physical.x);
	
	
}