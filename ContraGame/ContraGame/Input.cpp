#include "Input.h"


CInput::CInput(void)
{
	
}


int CInput::initInput(HINSTANCE hInstance)
{
	HRESULT result;
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_dinput, NULL);

	if (result != DI_OK)
	{
		return 0;
	}
	result = m_dinput->CreateDevice(GUID_SysKeyboard, &m_dinputkeyboard, NULL);
	if (result != DI_OK)
	{
		return 0;
	}
	return 1;
}
int CInput::initKeyboard(HWND _wndhandle)
{
	HRESULT result;
	result = m_dinputkeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (result != DI_OK)
	{
		return 0;
	}
	result = m_dinputkeyboard->SetCooperativeLevel(_wndhandle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
	{
		return 0;
	}
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;
	m_dinputkeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	result = m_dinputkeyboard->Acquire();
	return 1;
}

void CInput::processKeyBoard()
{
	m_dinputkeyboard->Poll();

	for (int i = 0; i < 256; i++)
	{
		m_lastState[i] = m_keystate[i];
	}

	if (!SUCCEEDED(m_dinputkeyboard->GetDeviceState(256, (LPVOID)&m_keystate)))
	{
		m_dinputkeyboard->Acquire();
	}
	pollKeyBoard();

}
bool CInput::onKeyDown(int key)
{
	if ((this->m_keystate[key] & 0x80) && !(this->m_lastState[key] && 0x80))
	{	
		return true;
	}
	else
	{		
		return false;
	}
}
bool CInput::onKeyUp(int key)
{
	if (!(this->m_keystate[key] & 0x80) && (this->m_lastState[key] && 0x80))
	{		
		return true;
	}
	else
	{	
		return false;
	}
}
int CInput::KeyDown(int key)
{
	return (m_keystate[key] && 0x80) > 0;
}

void CInput::pollKeyBoard()
{
	m_dinputkeyboard->GetDeviceState(sizeof(m_keystate), (LPVOID)&m_keystate);
}
void CInput::killKeyboard()
{
	if (m_dinputkeyboard != NULL)
	{
		m_dinputkeyboard->Unacquire();
		m_dinputkeyboard->Release();
		m_dinputkeyboard = NULL;
	}
}
LPDIRECTINPUTDEVICE8 CInput::getKeyBoard()
{
	return m_dinputkeyboard;
}
CInput::~CInput(void)
{
}

