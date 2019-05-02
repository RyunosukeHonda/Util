/**
* @file TitleSequencer.cpp
* @brief �^�C�g���V�[�P���T�[�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "TitleSequencer.h"

TitleSequencer::TitleSequencer() 
{
}

TitleSequencer::~TitleSequencer()
{
}

void TitleSequencer::update(IInput & input)
{
	mCurrentState->update(input);
	stateEndCheck();
}

void TitleSequencer::draw(IRenderer & renderer)
{
	mCurrentState->draw(renderer);
}

/* End of File *****************************************************/