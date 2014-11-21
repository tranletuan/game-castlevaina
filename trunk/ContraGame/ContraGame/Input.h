#ifndef INPUT_H_
#define INPUT_H_
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE    1024 
#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button] & 0x80)
#define DIRECTINPUT_VERSION 0x0800


class CInput
{
private:
	LPDIRECTINPUTDEVICE8 m_dinputkeyboard;
	DIDEVICEOBJECTDATA m_keyEvents[KEYBOARD_BUFFER_SIZE];
	BYTE m_keystate[256];
	int m_keyDown;
	int m_keyUp;
	
	BYTE m_lastState[256];
	LPDIRECTINPUT8 m_dinput;
public:

	CInput(void);
	CInput(HINSTANCE hInstance);
	~CInput(void);
	
	int initInput(HINSTANCE hInstance);
	int initKeyboard(HWND);
	void pollKeyBoard();
	void killKeyboard();
	int KeyDown(int);
	void processKeyBoard();
	bool onKeyDown(int);
	bool onKeyUp(int);
	LPDIRECTINPUTDEVICE8 getKeyBoard();


};
#endif


