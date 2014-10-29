#include "world_test.h"

WorldTest::WorldTest(int cmd_show) : CGame(cmd_show)
{
	this->cmd_show = cmd_show;
	this->background = new CBackground(L"map1", 32);
	this->bill = new CBill(D3DXVECTOR3(20, 135, 0), 34);
	this->bill2 = new CBill(D3DXVECTOR3(100, 135, 0), 34);
	this->bullet = new CMBullet(D3DXVECTOR3(100, 135, 0), 0, 1, BULLET_V);

}

WorldTest::~WorldTest()
{
	
}

void WorldTest::LoadResources(LPDIRECT3DDEVICE9 d3d_device)
{
	background->LoadResources();
	bill->LoadResources();
	bill2->LoadResources();
	bullet->LoadResources();
}

void WorldTest::RenderFrame(LPDIRECT3DDEVICE9 d3d_device)
{
	//background->Draw();
	bill->Draw();
	bill2->Draw();
	DisplayText(to_string(bullet->_physical.bounds.left) + " : " + to_string(bullet->_physical.bounds.right) + " : " + to_string(bullet->_physical.bounds.right - bullet->_physical.bounds.left));
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
	default:
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
	bullet->Update(delta_time);

	camera->UpdateCamera(bill->_physical.x);
	
	
}