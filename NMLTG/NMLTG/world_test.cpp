#include "world_test.h"

WorldTest::WorldTest(int cmd_show) : Game(cmd_show)
{
	this->cmd_show = cmd_show;
}

void WorldTest::RenderFrame(LPDIRECT3DDEVICE9 d3d_device, int delta)
{
	kSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	background->Draw(0, 0);
	kSpriteHandler->End();
}
void WorldTest::LoadResources(LPDIRECT3DDEVICE9 d3d_device)
{
	background = new Texture(L"H:\\Users\\Tran\\Desktop\\Map 1\\Map 1_0\\1_0.png");
}
void WorldTest::ProcessInput(LPDIRECT3DDEVICE9 d3d_device, int delta){} //Xử lý phím
void WorldTest::OnKeyDown(int key_code){}
void WorldTest::OnKeyUp(int key_code){}
void WorldTest::GameUpdate(int delta_time){}