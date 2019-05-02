/**
* @file PlayerGameSet.cpp
* @brief �v���C���[������ԃN���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "PlayerGameSet.h"

#include "Player.h"
#include "Screen.h"

PlayerGameSet::PlayerGameSet(Player* pPlayer) :
	mpPlayer(pPlayer),
	mResultImage(TextureID::WIN, 1.0f)
{
	//�v���C���[�ԍ��ɉ�����UI�ʒu��ݒ�
	mResultImage.Position = { 0, (float)Screen::WINDOW_HEIGHT / 4.0f - (float)Screen::WINDOW_HEIGHT / 2.0f * (float)pPlayer->Index };
}

PlayerGameSet::~PlayerGameSet()
{
}

void PlayerGameSet::init()
{
	//����ł��邩�ǂ����ŏ��s�摜��I��
	if (mpPlayer->isDead())
	{
		mResultImage.Scale = { 500, 100 };
		mResultImage.setID(TextureID::LOSE);
	}
	else
	{
		mResultImage.Scale = { 500, 100 };
		mResultImage.setID(TextureID::WIN);
	}
	mResultImage.init();
}

void PlayerGameSet::shutdown()
{
}

bool PlayerGameSet::isEnd()
{
	//�����I�ɃV�[�����I������̂őJ�ڂ���K�v�Ȃ�
	return false;
}

EPlayerState PlayerGameSet::next()
{
	//���ۂɑJ�ڂ͂��Ȃ�
	return EPlayerState::IDLE;
}

void PlayerGameSet::update(IInput & input)
{

}

void PlayerGameSet::fixedUpdate(float dt)
{
	//����ł�����|�ꂳ����
	if (mpPlayer->isDead())
	{
		mpPlayer->EulerAngle += {0, 0, 0.5f};
	}
}

void PlayerGameSet::lateUpdate(IInput & input)
{
}

void PlayerGameSet::draw(IRenderer & renderer)
{
	mResultImage.draw(renderer);
}

void PlayerGameSet::onCollisionEnter(ACollider * other)
{
}

void PlayerGameSet::gameSet()
{
}

/* End of File *****************************************************/