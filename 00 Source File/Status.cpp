/**
* @file Status.cpp
* @brief �X�e�[�^�X�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "Status.h"

Status::Status(int hp) :
	mHP(hp),
	mMaxHP(hp)
{
}

Status::~Status()
{
}

void Status::init()
{
	mHP = mMaxHP;
}

void Status::damage(const int & damage)
{
	mHP -= damage;
}

bool Status::isDead() const
{
	return mHP <= 0;
}

void Status::draw(IRenderer & renderer) const
{
}

/* End of File *****************************************************/