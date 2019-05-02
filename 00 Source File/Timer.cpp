/**
* @file Timer.cpp
* @brief タイマークラス(加算式)実装ファイル
* @author Ryunosuke Honda.
*/
#include "Timer.h"


/*
	コンストラクタ
*/
Timer::Timer() :
	m_Limit(1.0f * ToDWORD),
	m_Current(0.0f),
	m_Start(0)
{
}

Timer::Timer(float limit) :
	m_Limit(limit * ToDWORD),
	m_Current(0.0f),
	m_Start(0)
{
}

/*
	デストラクタ
*/
Timer::~Timer()
{
}

void Timer::init()
{
	m_Current = 0.0f;
	m_Start = 0;
}

void Timer::init(float limit)
{
	m_Limit = limit * ToDWORD;
	m_Current = 0.0f;
	m_Start = 0;
}

void Timer::update()
{
	if (m_Start == 0)
		m_Start = timeGetTime();
	
	time_t t = timeGetTime() - m_Start;
	m_Current = min(t, m_Limit);
}

bool Timer::isEnd()
{
	return m_Current >= m_Limit;
}

float Timer::rate()
{
	//0.0 -> 1.0
	return (float)m_Current / (float)m_Limit;
}

float Timer::getCurrent()
{
	return (float)m_Current * ToSecond;
}

void Timer::forcedEnd()
{
	m_Limit = m_Current;
}

/****** End of File *****************************************************/
