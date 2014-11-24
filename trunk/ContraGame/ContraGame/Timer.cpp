#include "Timer.h"

CTimer::CTimer(void)
{
	getSecondPerTick();
	m_frameRate = 0;
	m_deltaTime = 0;
	m_countFrame = 0;
	t_deltaTime = 0;
}

void CTimer::getSecondPerTick()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_coutPerSec);
	m_timeScale = 1.0f / (float)m_coutPerSec;
}

void CTimer::startCount()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_timeStart);
}

void CTimer::endCount()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_timeEnd);
	t_deltaTime = (m_timeEnd - m_timeStart) * m_timeScale;
	if (m_lockFps > 0.0f)
	{
		while (t_deltaTime < 1.0f / m_lockFps)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&m_timeEnd);
			t_deltaTime = (m_timeEnd - m_timeStart) * m_timeScale;
		}
	}

	m_timeStart = m_timeEnd;
	m_deltaTime += t_deltaTime;
	m_countFrame++;
	if (m_deltaTime >= 1.0f)
	{
		m_frameRate = m_countFrame;
		m_countFrame = 0;
		m_deltaTime = 0.0f;
	}
}


void CTimer::setMaxFps(float _maxFps)
{
	m_lockFps = _maxFps;
}

float CTimer::getDeltaTime()
{
	return (float)(1.0f / m_lockFps) * 1000;
}

float CTimer::getTime()
{
	return m_deltaTime;
}

CTimer::~CTimer(void)
{
}
