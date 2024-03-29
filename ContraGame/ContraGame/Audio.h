#ifndef _CAUDIO_H_
#define _CAUDIO_H_
#include "dsutil.h"
#include <string>

using namespace std;

//primary DirectSound object
extern CSoundManager *dsound;

//function prototypes
class CAudio
{
public:
	CAudio(HWND);	
	CSound *LoadSound(char*);
	void playSound(CSound *);
	void loopSound(CSound *);
	void stopSound(CSound *);
	static bool m_isSoundOff;
};

#endif

