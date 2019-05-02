/**
* @file ACharacter.cpp
* @brief 
* @author Ryunosuke Honda.
*/
#include "ACharacter.h"

ACharacter::ACharacter(int hp) :
	mStatus(hp)
{
}

bool ACharacter::isDead() const
{
	return mStatus.isDead();
}


/* End of File *****************************************************/