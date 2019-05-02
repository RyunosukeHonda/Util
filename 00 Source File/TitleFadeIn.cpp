/**
* @file TitleFadeIn.cpp
* @brief �^�C�g���E�t�F�[�h�C����ԃN���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "TitleFadeIn.h"

#include "IInput.h"

TitleFadeIn::TitleFadeIn() :
	mFadeIn()
{
}

TitleFadeIn::~TitleFadeIn()
{
}

void TitleFadeIn::init()
{
	mFadeIn.init();
	mFadeIn.start(2.0f);
}

void TitleFadeIn::shutdown()
{
}

bool TitleFadeIn::isEnd()
{
	return mFadeIn.isEnd();
}

ETitleState TitleFadeIn::next()
{
	return ETitleState::IDLING;
}

void TitleFadeIn::update(IInput & input)
{
	mFadeIn.update();
	//�X�^�[�g�{�^���������ꂽ��t�F�[�h���΂�
	for (int i = 0; i < GameDef::PLAYER_COUNT; i++)
	{
		if (input.isButtonDown(static_cast<EPlayerIndex>(i), XINPUT_GAMEPAD_START))
		{
			mFadeIn.forcedEnd();
			break;
		}
	}
}

void TitleFadeIn::draw(IRenderer & renderer)
{
	mFadeIn.draw(renderer);
}

/* End of File *****************************************************/