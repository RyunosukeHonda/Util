/**
* @file APlayableCharacter.cpp
* @brief 操作可能なキャラクタークラス実装ファイル
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