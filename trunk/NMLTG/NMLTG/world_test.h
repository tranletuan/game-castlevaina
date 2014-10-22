#ifndef _WORLD_TEST_H_
#define _WORLD_TEST_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "global.h"
#include "CGame.h"
#include "CResourcesManager.h"
#include "CBackground.h"
#include "Utils.h"
#include "CBill.h"

class WorldTest : public CGame
{
public:
	WorldTest(int cmd_show);
	~WorldTest();
protected:
	CResourcesManager *texture_manager;
	CBackground* background;
	CBill* bill;
	CBill* bill2;
	DWORD delta;
	int test, test2;

	void RenderFrame(LPDIRECT3DDEVICE9 d3d_device);
	void LoadResources(LPDIRECT3DDEVICE9 d3d_device);
	void ProcessInput(LPDIRECT3DDEVICE9 d3d_device, int delta); //Xử lý phím
	void OnKeyDown(int key_code);
	void OnKeyUp(int key_code);
	void GameUpdate(int delta_time);
};
#endif // !_WORLD_TEST_H_
