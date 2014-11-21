#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>
#include <tchar.h>

class CTimer
{
private:
	__int64 m_coutPerSec; 
	float m_timeScale;
	int m_countFrame;
	int m_frameRate;
	float m_deltaTime;
	float t_deltaTime;
	float m_lockFps;

public:	
	__int64 m_timeStart;
	__int64 m_timeEnd;

	CTimer(void);
	~CTimer(void);

	void getSecondPerTick();
	void startCount();
	void endCount();
	void stopWatch();
	void setMaxFps(float);
	float getDeltaTime();
	float getTime();
	unsigned short GetNumDeltaTime(LPSTR lpstrFrameRate = NULL);

};


#endif