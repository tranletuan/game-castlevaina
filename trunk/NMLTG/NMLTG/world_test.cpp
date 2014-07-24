#include "world_test.h"

WorldTest::WorldTest(int cmd_show) : Game(cmd_show)
{
	this->cmd_show = cmd_show;
	i = kScreenWidth / 2;
	camera = new Camera();
	background = new Background(L"1_0", 16);
}

WorldTest::~WorldTest()
{
	delete background;
	delete camera;
}

void WorldTest::RenderFrame(LPDIRECT3DDEVICE9 d3d_device, int delta)
{
	kSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	background->Draw(*camera);
	kSpriteHandler->End();
}
void WorldTest::LoadResources(LPDIRECT3DDEVICE9 d3d_device)
{
	background->LoadResources();
}
void WorldTest::ProcessInput(LPDIRECT3DDEVICE9 d3d_device, int delta)
{
	if (IsKeyDown(DIK_RIGHT))
	{
		i += 0.045f * delta;
		camera->UpdateCamera(i);
	}
} //Xử lý phím

void WorldTest::OnKeyDown(int key_code)
{
	switch (key_code)
	{
	case DIK_RIGHT:
		//i = kScreenWidth / 2;
		//i += 10;
		//camera->UpdateCamera(i);
		break;
	default:
		break;
	}
}
void WorldTest::OnKeyUp(int key_code)
{
	switch (key_code)
	{
	/*case DIK_RIGHT:
		
		break;
	*/
	}
}
void WorldTest::GameUpdate(int delta_time)
{
	
}