///**
//* @file BattlePlayer.cpp
//* @brief 対戦モード用プレイヤークラス実装ファイル
//* @author Ryunosuke Honda.
//*/
//#include "BattlePlayer.h"
//
//#include "FPSCamera.h"
//#include "IRenderer.h"
//#include "IInput.h"
//#include "Bullet.h"
//#include "Screen.h"
//#include "Gun.h"
//#include <dinput.h>
//
//BattlePlayer::BattlePlayer(EPlayerIndex index, int hp, IAddable<ACharacter>* characterMgr, IAddable<ACollider>* colliderMgr) :
//	base(hp, characterMgr, colliderMgr),
//	mIndex(index)
//{
//	mTag = ETag::PLAYER;
//	//プレイヤー番号に応じたチームのレイヤーを設定
//	Layer = static_cast<ELayer>(mIndex + 2);
//	mCamera.Layer = Layer;
//}
//
//BattlePlayer::~BattlePlayer()
//{
//}
//
//void BattlePlayer::init()
//{
//	///mIndexに対応した初期設定を行います
//
//	LocalPosition = Vector3(0, 5, 10) * (mIndex + 1);
//	(Vector3)LocalEulerAngle = Vector3(0, 0, 0);
//
//	//自身をカリングするよう設定する
//	mCamera.setCullingLayer(Layer);
//	//ビューポートの設定
//	D3D11_VIEWPORT vp;
//	vp.Width = Screen::WINDOW_WIDTH;
//	vp.Height = Screen::WINDOW_HEIGHT / 2;
//	vp.MinDepth = 0.0f;
//	vp.MaxDepth = 1.0f;
//	vp.TopLeftX = 0;
//	vp.TopLeftY = (Screen::WINDOW_HEIGHT / 2) * mIndex;
//	mCamera.Viewport = vp;
//}
//
//void BattlePlayer::update(IInput & input)
//{
//	//キー操作
//	if (GetKeyState('A') & 0x80) turnLeft(3);
//	if (GetKeyState('D') & 0x80) turnRight(3);
//	if (GetKeyState('W') & 0x80) moveForward(0.1);
//	if (GetKeyState('S') & 0x80) moveBackward(0.1);
//	//if (GetKeyState('Z') & 0x80) mCamera.rotateCamera(Vector2(1, 0));
//	//if (GetKeyState('X') & 0x80) mCamera.rotateCamera(Vector2(0, 1));
//
//	mCamera.RotateAmount += input.getRightStick(mIndex) * 0.005f;
//	//mCamera.RotateAmount = { input.getMousePosition().x/ 100, (input.getMousePosition().y + 720) / 1000 };
//
//	mShot->update();
//	//*
//	if (mIndex == EPlayerIndex::ONE && input.isMouseButtonDown(EMouseButton::LEFT))
//	{
//		mShot->shot(&mCamera);
//	}
//	if (mIndex == EPlayerIndex::TWO && input.isMouseButtonDown(EMouseButton::RIGHT))
//	{
//		mShot->shot(&mCamera);
//	}
//	/*/
//	if (input.getRightTrigger(mIndex) > 0.5f)
//	{
//		mShot->shot(&mCamera);
//	}
//	//*/
//}
//
//void BattlePlayer::onCollisionEnter(ACollider * other)
//{
//	cout << mIndex;
//	cout << " , ";
//	cout << "Enter" << endl;
//}
//
///* End of File *****************************************************/