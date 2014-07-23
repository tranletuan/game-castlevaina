#ifndef _WORLD_TEST_H_
#define _WORLD_TEST_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "global.h"
#include "game.h"
#include "sprite.h"
class WorldTest : public Game
{
public:
	WorldTest(int cmd_show);

protected:
	Texture *background;

	void RenderFrame(LPDIRECT3DDEVICE9 d3d_device, int delta);
	void LoadResources(LPDIRECT3DDEVICE9 d3d_device);
	void ProcessInput(LPDIRECT3DDEVICE9 d3d_device, int delta); //Xử lý phím
	void OnKeyDown(int key_code);
	void OnKeyUp(int key_code);
	void GameUpdate(int delta_time);
};
#endif // !_WORLD_TEST_H_
