#include "world_test.h"

WorldTest::WorldTest(int cmd_show) : Game(cmd_show)
{
	this->cmd_show = cmd_show;
	i = 0;
	camera = new Camera();

	background = new Background(L"1_0", 16);
	background1 = new Background(L"1_1", 16);
	background2 = new Background(L"1_2", 16);

	//simon = new Simon(D3DXVECTOR2(32, 64));
	kGround = 32;
}

WorldTest::~WorldTest()
{
	delete background;
	delete camera;
}

void WorldTest::RenderFrame(LPDIRECT3DDEVICE9 d3d_device, int delta)
{
	background->Draw(*camera);
	//simon->Draw(*camera);
}

void WorldTest::LoadResources(LPDIRECT3DDEVICE9 d3d_device)
{
	background->LoadResources();
	background1->LoadResources();
	background2->LoadResources();
	//simon->LoadResources();
	
}
void WorldTest::ProcessInput(LPDIRECT3DDEVICE9 d3d_device, int delta)
{
	/*if (IsKeyDown(DIK_DOWN))
	{
		simon->Stoop();
	}
	else
	{
		if (IsKeyDown(DIK_RIGHT))
		{
			simon->MoveRight();
		}
		else if (IsKeyDown(DIK_LEFT))
		{
			simon->MoveLeft();
		}
	}*/
	
} //Xử lý phím

void WorldTest::OnKeyDown(int key_code)
{
	/*switch (key_code)
	{
	case DIK_SPACE:
		simon->Jump();
		break;
	default:
		break;
	}*/
}
void WorldTest::OnKeyUp(int key_code)
{
	/*switch (key_code)
	{
	case DIK_RIGHT:
	case DIK_LEFT:
	case DIK_UP:
	case DIK_DOWN:
	case DIK_SPACE:
		simon->Stand();
	break;
	
	}*/
}
void WorldTest::GameUpdate(int delta_time)
{
	//simon->Update(delta_time);
	//camera->UpdateCamera(simon->pos.x);
}