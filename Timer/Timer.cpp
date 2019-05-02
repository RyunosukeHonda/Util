/**
* @file Timer.cpp
* @brief �^�C�}�[�N���X(���Z��)�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "Timer.h"

#include <iostream>

/*
	�R���X�g���N�^
*/
Timer::Timer() :
	mLimit(1.0f * ToDWORD),
	mCurrent(0.0f),
	mStart(0)
{
}

Timer::Timer(float limit) :
	mLimit(limit * ToDWORD),
	mCurrent(0.0f),
	mStart(0)
{
}

/*
	�f�X�g���N�^
*/
Timer::~Timer()
{
}

void Timer::init()
{
	mCurrent = 0.0f;
	mStart = 0;
}

void Timer::init(float limit)
{
	mLimit = limit * ToDWORD;
	mCurrent = 0.0f;
	mStart = 0;
}

void Timer::update()
{
	if (mStart == 0)
		mStart = timeGetTime();

	time_t t = timeGetTime() - mStart;
	mCurrent = min(t, mLimit);
}

bool Timer::isEnd()
{
	return mCurrent >= mLimit;
}

float Timer::rate()
{
	//0.0 -> 1.0
	return (float)mCurrent / (float)mLimit;
}

float Timer::getCurrent()
{
	return (float)mCurrent * ToSecond;
}

void Timer::forcedEnd()
{
	mLimit = mCurrent;
}

/****** End of File *****************************************************/
