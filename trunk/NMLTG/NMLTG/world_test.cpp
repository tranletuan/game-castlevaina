#include "world_test.h"

WorldTest::WorldTest(int cmd_show) : CGame(cmd_show)
{
	this->cmd_show = cmd_show;
	this->background = new CBackground(L"map1", 32);
	this->bill = new CBill(D3DXVECTOR3(50, 130, 0), 34);
	this->bill2 = new CBill(D3DXVECTOR3(200, 135, 0), 34);
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
	//background->Draw();
	bill->Draw();
	bill2->Draw();

	//string show = to_string(bill->_physical.tx_entry) + " : " + to_string(bill->_physical.current_vx) + " : " + to_string(test);
	//string show = to_string(bill->_physical.current_vy) + " : " + to_string(bill->_physical.dy_entry);
	string show = to_string(test);
	DisplayText(show);
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
	
	delta = delta_time;
	bill->Update(delta_time);
	bill2->Update(delta_time);

	test = bill->_physical.Collision(&bill2->_physical);


	//test = bill->_physical.vx * delta_time;

	camera->UpdateCamera(bill->_physical.x);
}