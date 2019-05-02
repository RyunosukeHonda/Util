/**
* @file GameMainCountdown.cpp
* @brief �Q�[�����C���V�[����ԁE�J�E���g�_�E���N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "GameMainCountdown.h"

#include "IRenderer.h"
#include "EPlayerIndex.h"

GameMainCountdown::GameMainCountdown() :
	mTimer(),
	mCountImage()
{
	//�v���C���[�ԍ���UI�|�W�V�����ɕϊ�����}�b�v�A�Ƃ肠������l��
	std::unordered_map<int, Vector2> indexToPosition;
	indexToPosition[EPlayerIndex::ONE] = Vector2(0, 200);
	indexToPosition[EPlayerIndex::TWO] = Vector2(0, -200);

	//�v���C���[�l�������[�v
	for (int i = 0; i < GameDef::PLAYER_COUNT; i++)
	{
		//�J�E���g�_�E���p��UI�I�u�W�F�N�g���쐬
		UIImageObject* image;
		//START!!
		image = new UIImageObject(TextureID::START);
		image->Position = indexToPosition[i];
		image->Scale = { 300, 100 };
		mCountImage[i][START] = CountImagePointer(image);
		//1
		image = new UIImageObject(TextureID::COUNT_ONE);
		image->Position = indexToPosition[i];
		image->Scale = { 100, 100 };
		mCountImage[i][ONE] = CountImagePointer(image);
		//2
		image = new UIImageObject(TextureID::COUNT_TWO);
		image->Position = indexToPosition[i];
		image->Scale = { 100, 100 };
		mCountImage[i][TWO] = CountImagePointer(image);
		//3
		image = new UIImageObject(TextureID::COUNT_THREE);
		image->Position = indexToPosition[i];
		image->Scale = { 100, 100 };
		mCountImage[i][THREE] = CountImagePointer(image);
	}
}

GameMainCountdown::~GameMainCountdown()
{
}

void GameMainCountdown::init()
{
	mTimer.init(4.0f);
}

void GameMainCountdown::shutdown()
{
}

bool GameMainCountdown::isEnd()
{
	return mTimer.isEnd();
}

EGameMainState GameMainCountdown::next()
{
	return EGameMainState::BATTLE;
}

void GameMainCountdown::update(IInput & input)
{
	mTimer.update();
}

void GameMainCountdown::fixedUpdate(float dt)
{
}

void GameMainCountdown::lateUpdate(IInput & input)
{
}

void GameMainCountdown::draw(IRenderer & renderer)
{
	//���݂̃J�E���g�ɑΉ������摜��`�悷��
	int countNum = (int)(4.0f - mTimer.getCurrent());
	if (countNum > 3) return;

	for (int i = 0; i < GameDef::PLAYER_COUNT; i++)
	{
		mCountImage[i][countNum]->draw(renderer);
	}
}

/* End of File *****************************************************/