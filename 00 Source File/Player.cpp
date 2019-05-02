/**
* @file Player.cpp
* @brief プレイヤークラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "Player.h"

///State
#include "PlayerIdle.h"
#include "PlayerRun.h"
#include "PlayerAiming.h"
#include "PlayerGameSet.h"

#include "IRenderer.h"
#include "IInput.h"
#include "Gun.h"
#include "Screen.h"
#include "PlayerSettingDesc.h"
#include "SoundManager.h"

Player::Player(const PlayerSettingDesc& settingDesc) :
	APlayableCharacter(settingDesc.mHP),
	SphereCollider(settingDesc.mRadius),
	mIndex(settingDesc.mIndex),
	mFrame(0),
	mCamera(this),
	mShot(new Gun(settingDesc.mGenerateBulletFunc)),
	mDesc(FBXSkinID::player),
	mDamageEffect(ShaderTextureID::MONOCHROME, 1.0f)
{
	//タグ設定
	mTag = ETag::PLAYER;

	//プレイヤー番号に応じたチームのレイヤーを設定
	int index_to_layer = 2;
	Layer = static_cast<ELayer>(mIndex + index_to_layer);

	//銃弾生成時にカメラの情報を使用するためレイヤーにチーム番号を登録しておく
	mCamera.Layer = Layer;

	//描画記述子に自身を登録
	mDesc.mpTransform = this;

	//初期位置設定
	Position = settingDesc.mPosition;
	mInitPosition = Position;

	//ステートの生成
	add(EPlayerState::IDLE, new PlayerIdle(this));
	add(EPlayerState::RUN, new PlayerRun(this));
	add(EPlayerState::AIMING, new PlayerAiming(this));
	add(EPlayerState::GAME_SET, new PlayerGameSet(this));
	initState(EPlayerState::IDLE);

	//自身をカリングするよう設定する
	mCamera.setCullingLayer(Layer);

	//ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.Width = Screen::WINDOW_WIDTH;
	vp.Height = Screen::WINDOW_HEIGHT / 2;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = (Screen::WINDOW_HEIGHT / 2) * mIndex;
	mCamera.Viewport = vp;

	mDamageEffect.Position = { 0, (float)Screen::WINDOW_HEIGHT / 4.0f - (float)Screen::WINDOW_HEIGHT / 2.0f * (float)mIndex };
	mDamageEffect.Scale = { (float)Screen::WINDOW_WIDTH, (float)Screen::WINDOW_HEIGHT / 2.0f };
	mDamageEffect.setColor(Color4(1, 0, 0, 1));
}

Player::~Player()
{

}

void Player::rotateCamera(const Vector2 & amount)
{
	mCamera.RotateAmount += amount;
}

void Player::init()
{
	LocalPosition = mInitPosition;
	LocalEulerAngle = Vector3(0, 0, 0);

	float playerAngle = 3.14f * mIndex;
	float playerHeight = 0.8f;
	mCamera.init(Vector2(playerAngle, playerHeight));

	mStatus.init();
	initState(EPlayerState::IDLE);
}

void Player::lateUpdate(IInput & input)
{
	//カメラの更新を行う
	mCamera.update();

	//ステート終了確認
	stateEndCheck();
}

void Player::fixedUpdate(float dt)
{
	//移動処理
	mCurrentState->fixedUpdate(dt);
	//物理挙動
	ARigidBody::fixedUpdate(dt);

	//ステージ範囲外に出ないようクランプ
	Position = {
		CLAMP(Position.x, -GameDef::STAGE_WIDTH, GameDef::STAGE_WIDTH),
		Position.y,
		CLAMP(Position.z, -GameDef::STAGE_WIDTH, GameDef::STAGE_WIDTH),
	};
}

void Player::update(IInput& input)
{
	mCurrentState->update(input);

	//射撃はいつでも行える
	mShot->update();
	if (input.getRightTrigger(mIndex) > 0.5f)
	{
		mShot->shot(&mCamera);
	}
}

void Player::draw(IRenderer & renderer)
{
	renderer.render(&mDesc);
	mDamageEffect.draw(renderer);
	mCurrentState->draw(renderer);
}

void Player::renderExecute(IRenderer & renderer)
{
	renderer.setRenderCamera(&mCamera);
	renderer.renderExecute();
}

void Player::gameSet()
{
	mCurrentState->gameSet();
}

void Player::onCollisionEnter(ACollider * other)
{
	if (other->Tag == ETag::BULLET)
	{
		int damagePoint = 10;
		mStatus.damage(damagePoint);
		SoundManager::instance().play(SoundID::HIT, false);
		mDamageEffect.init();
	}
	mCurrentState->onCollisionEnter(other);
}

void Player::onCollisionStay(ACollider * other)
{
}

void Player::onCollisionExit(ACollider * other)
{
}

void Player::move(const Vector2& amount)
{
	//前後方向移動
	Vector3 v = mCamera.Forward * amount.y;
	v.y = 0;
	//D3DXVec3Normalize(&v, &v);
	LocalPosition += Vector3(v.x, 0, v.z);
	///FIXME Magic
	//左右方向移動
	v = mCamera.Forward * -amount.x;
	v.y = 0;
	//D3DXVec3Normalize(&v, &v);
	D3DXVec3Cross(&v, &v, &Vector3(0, 1, 0));
	LocalPosition += Vector3(v.x, 0, v.z);

	//歩行アニメーション進める
	mFrame++;
	if (mFrame >= 25) mFrame = 0;
	mDesc.mFrame = mFrame * 4;
}

/* End of File *****************************************************/