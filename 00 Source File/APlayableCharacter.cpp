/**
* @file APlayableCharacter.cpp
* @brief ����\�ȃL�����N�^�[�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "APlayableCharacter.h"

APlayableCharacter::APlayableCharacter(int hp) :
	mStatus(hp)
{
}

bool APlayableCharacter::isDead() const
{
	return mStatus.isDead();
}

/* End of File *****************************************************/