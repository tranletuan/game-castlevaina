#include "world_test.h"

WorldTest::WorldTest(int cmd_show) : CGame(cmd_show)
{
	this->cmd_show = cmd_show;
	this->background = new CBackground(L"map1", 32);
}

WorldTest::~WorldTest()
{
}

void WorldTest::LoadResources(LPDIRECT3DDEVICE9 d3d_device)
{
	background->LoadResources();
}

void WorldTest::RenderFrame(LPDIRECT3DDEVICE9 d3d_device)
{
	background->Draw();
}


void WorldTest::ProcessInput(LPDIRECT3DDEVICE9 d3d_device, int delta)
{
	
	
} //Xử lý phím

void WorldTest::OnKeyDown(int key_code)
{
	
}
void WorldTest::OnKeyUp(int key_code)
{
	
	
}
void WorldTest::GameUpdate(int delta_time)
{
	
}