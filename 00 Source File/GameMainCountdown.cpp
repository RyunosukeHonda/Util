/**
* @file GameMainCountdown.cpp
* @brief ゲームメインシーン状態・カウントダウンクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "GameMainCountdown.h"

#include "IRenderer.h"
#include "EPlayerIndex.h"

GameMainCountdown::GameMainCountdown() :
	mTimer(),
	mCountImage()
{
	//プレイヤー番号をUIポジションに変換するマップ、とりあえず二人分
	std::unordered_map<int, Vector2> indexToPosition;
	indexToPosition[EPlayerIndex::ONE] = Vector2(0, 200);
	indexToPosition[EPlayerIndex::TWO] = Vector2(0, -200);

	//プレイヤー人数分ループ
	for (int i = 0; i < GameDef::PLAYER_COUNT; i++)
	{
		//カウントダウン用のUIオブジェクトを作成
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
	//現在のカウントに対応した画像を描画する
	int countNum = (int)(4.0f - mTimer.getCurrent());
	if (countNum > 3) return;

	for (int i = 0; i < GameDef::PLAYER_COUNT; i++)
	{
		mCountImage[i][countNum]->draw(renderer);
	}
}

/* End of File *****************************************************/