#include "world_test.h"

WorldTest::WorldTest(int cmd_show) : CGame(cmd_show)
{
	this->cmd_show = cmd_show;
	this->background = new CBackground(L"map1", 32);
	this->bill = new CBill(D3DXVECTOR3(20, 135, 0), 34);
	this->bill2 = new CBill(D3DXVECTOR3(100, 135, 0), 34);
	/*
	this->bill->_physical.vx = 0.1f;
	this->bill->_physical.vy = 0.2f;

	this->bill2->_physical.vx = 0.2f;
	this->bill2->_physical.vy = 0.1f;
	this->bill2->SetGunDirection(Down);*/

}

WorldTest::~WorldTest()
{
}

void WorldTest::LoadResources(LPDIRECT3DDEVICE9 d3d_device)
{
	background->LoadResources();
	bill->LoadResources();
	bill2->LoadResources();
}

void WorldTest::RenderFrame(LPDIRECT3DDEVICE9 d3d_device)
{
	background->Draw();
	bill->Draw();
	bill2->Draw();
}


void WorldTest::ProcessInput(LPDIRECT3DDEVICE9 d3d_device, int delta)
{
	//Set phím di chuyển trái phải
	if (IsKeyDown(DIK_D))
	{
		bill->MovingRight();
	}
	else if (IsKeyDown(DIK_A))
	{
		
		bill->MovingLeft();
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
	camera->UpdateCamera(bill->_physical.x);

	int cd = bill->_physical.Collision(&bill2->_physical);

	////bill 2
	//if (bill2->_physical.bounds.right > kScreenWidth ||
	//	bill2->_physical.bounds.left < 0 || cd == 1 || cd == 2)
	//{
	//	bill2->_physical.vx *= -1;
	//}

	//if (bill2->_physical.bounds.top > kScreenHeight ||
	//	bill2->_physical.bounds.bottom < 0 || cd == 3 || cd == 4)
	//{
	//	bill2->_physical.vy *= -1;
	//}

	////bill 1s
	//if (bill->_physical.bounds.right > kScreenWidth ||
	//	bill->_physical.bounds.left < 0 || cd == 1 || cd == 2)
	//{
	//	bill->_physical.vx *= -1;
	//}

	//if (bill->_physical.bounds.top > kScreenHeight ||
	//	bill->_physical.bounds.bottom < 0 || cd == 3 || cd == 4)
	//{
	//	bill->_physical.vy *= -1;
	//}

	
}