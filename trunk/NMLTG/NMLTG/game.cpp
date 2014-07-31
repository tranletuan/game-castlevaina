#include "game.h"
#include <Windows.h>
#include <time.h>

Game::Game(int cmd_show)
{
	this->cmd_show = cmd_show;
}

Game::~Game() {}

void Game::GameInit()
{
	InitWindow();
	InitDirectX();
	InitInput();
	LoadResources(kDevice);
}

void Game::GameRun()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	DWORD frame_start = GetTickCount();
	DWORD tick_per_fram = 100 / kFrameRate;

	//Vòng lặp chính quản lý thông điệp
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		delta_time = now - frame_start;

		if (delta_time >= tick_per_fram)
		{
			//Vẽ các thành phần trong game;
			RenderAll();
			frame_start = now;
		}

		GameUpdate(delta_time);

		//Xử lý phím điều khiển
		ProcessKeyboard();
		ProcessInput(kDevice, delta_time);
	}
}

void Game::GameEnd()
{
	if (kDevice != NULL) kDevice->Release();
	if (kDirectX != NULL) kDirectX->Release();
	if (kSpriteHandler != NULL) kSpriteHandler->Release();
	if (kKeyBoard != NULL) kKeyBoard->Release();
	if (kDirectInput != NULL) kDirectInput->Release();
}

LRESULT CALLBACK Game::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool Game::InitWindow()
{
	WNDCLASSEX wcex;

	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbWndExtra = 0;

	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = NULL;
	wcex.hIconSm = NULL;
	wcex.hInstance = kHInstance;

	wcex.lpfnWndProc = (WNDPROC)Game::WinProc;
	wcex.lpszClassName = kGameName;
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wcex);

	//Cửa sổ hoặc toàn màn hình
	DWORD screen_style;
	if (kIsFullScreen)
	{
		screen_style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else
	{
		screen_style = WS_OVERLAPPEDWINDOW; // Cửa sổ
	}

	//Khởi tạo cửa 
	kHWND = CreateWindow(
		kGameName,
		kGameName,
		screen_style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		kScreenWidth,
		kScreenHeight,
		NULL,
		NULL,
		kHInstance,
		NULL);

	if (!kHWND)
	{
		GLMessage(L"Init hWnd Fail");
		return false;
	}

	if (!kHInstance)
	{
		GLMessage(L"Init hInstance Fail");
		return false;
	}

	ShowWindow(kHWND, this->cmd_show);
	UpdateWindow(kHWND);

	return true;
}

bool Game::InitDirectX()
{
	kDirectX = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3d_params;

	ZeroMemory(&d3d_params, sizeof(D3DPRESENT_PARAMETERS));

	d3d_params.BackBufferCount = 1;
	d3d_params.BackBufferFormat = kBackBufferFormat;
	d3d_params.BackBufferHeight = kScreenHeight;
	d3d_params.BackBufferWidth = kScreenWidth;
	
	d3d_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3d_params.Windowed = !kIsFullScreen;
	d3d_params.hDeviceWindow = kHWND;

	kDirectX->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_REF,
		kHWND,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3d_params,
		&kDevice);

	if (!kDevice)
	{
		GLMessage(L"Init Device Fail");
		return false;
	}
		
	srand(time(NULL));
	kDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &kBackBuffer);
	D3DXCreateSprite(kDevice, &kSpriteHandler);

	return true;
}

bool Game::InitInput()
{
	HRESULT hrs;

	//Khởi tạo đối tượng đầu vào
	hrs = DirectInput8Create(
		kHInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&kDirectInput,
		NULL);

	if (hrs != D3D_OK)
	{
		GLMessage(L"Init Input Fail");
		return false;
	}

	hrs = kDirectInput->CreateDevice(GUID_SysKeyboard, &kKeyBoard, NULL);
	hrs = kKeyBoard->SetDataFormat(&c_dfDIKeyboard);
	hrs = kKeyBoard->SetCooperativeLevel(kHWND, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//buffer input
	DIPROPDWORD dipdw;

	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.dwData = GL_KEY_BUFFER_SIZE;

	hrs = kKeyBoard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	hrs = kKeyBoard->Acquire();

	if (hrs != D3D_OK)
	{
		GLMessage(L"Init Keyboard Fail");
		return false;
	}

	return true;
}

void Game::ProcessKeyboard()
{
	//Quản lý các phím tác động
	kKeyBoard->GetDeviceState(sizeof(key_states), key_states);

	//Thoát khi nhấn phím escape
	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(kHWND, WM_QUIT, 0, 0);
	}

	//Lấy tất cả các phím được thực hiện
	DWORD dw_elements = GL_KEY_BUFFER_SIZE;
	HRESULT hrs = kKeyBoard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), key_events, &dw_elements, 0);

	//Duyệt tất cả các phím được thực hiện
	for (DWORD i = 0; i < dw_elements; i++)
	{
		int key_code = key_events[i].dwOfs;
		int key_state = key_events[i].dwData;

		if ((key_state & 0x80) > 0)
		{
			OnKeyDown(key_code);
		}
		else
		{
			OnKeyUp(key_code);
		}
	}
}

int Game::IsKeyDown(int key_code)
{
	return (key_states[key_code] & 0x80) > 0;
}

void Game::RenderAll()
{
	//kDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 128, 128), 1.0f, 0);
	if (kDevice->BeginScene())
	{
		kSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		RenderFrame(kDevice, delta_time);
		kSpriteHandler->End();
		kDevice->EndScene();
	}

	kDevice->Present(NULL, NULL, NULL, NULL);
}

void Game::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int delta_time)
{
	d3ddv->ColorFill(kBackBuffer, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void Game::LoadResources(LPDIRECT3DDEVICE9 d3d_device) { }

void Game::ProcessInput(LPDIRECT3DDEVICE9 d3d_device, int delta_time) { }

void Game::OnKeyDown(int key_code) { }

void Game::OnKeyUp(int key_code) { }

void Game::GameUpdate(int delta_time) { }
