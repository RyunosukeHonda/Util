/**
* @file Player.h
* @brief プレイヤークラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "APlayableCharacter.h"
#include "SphereCollider.h"
#include "StateMachineTemplate.h"
#include "EPlayerState.h"
#include "IPlayerState.h"
#include "FPSCamera.h"
#include "FBXSkinMeshRenderDesc.h"
#include <memory>
#include "UIDisappearingQuad.h"
#include "EPlayerIndex.h"

struct PlayerSettingDesc;
class IShotable;

/**
*	プレイヤークラス
*/
class Player : 
	public APlayableCharacter, 
	public SphereCollider,
	public StateMachineTemplate<EPlayerState, IPlayerState> 
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	Player(const PlayerSettingDesc& settingDesc);

	/**
	 * @fn
	 * デストラクタ
	 */
	~Player();

	/**
	* @fn
	* 移動処理
	*/
	void move(const Vector2& amount);

	/**
	* @fn
	* 移動処理
	*/
	void rotateCamera(const Vector2& amount);

	// APlayableCharacter を介して継承されました
	virtual void init() override;
	virtual void update(IInput& input) override;
	virtual void lateUpdate(IInput & input) override;
	virtual void fixedUpdate(float dt) override;
	virtual void draw(IRenderer & renderer) override;
	virtual void renderExecute(IRenderer & renderer) override;
	virtual void gameSet() override;
	
	// SphereCollider を介して継承されました
	virtual void onCollisionEnter(ACollider* other) override;
	virtual void onCollisionStay(ACollider* other) override;
	virtual void onCollisionExit(ACollider* other) override;

private:
	//!アニメーションフレーム
	PROPERTY_READWRITE(int, Frame);
	//!FPSカメラ
	FPSCamera mCamera;
	//!射撃機能インターフェース
	unique_ptr<IShotable> mShot;
	//!プレイヤー番号
	PROPERTY_READONLY(EPlayerIndex, Index);
	//!モデル描画用記述子
	FBXSkinMeshRenderDesc mDesc;
	//!初期化時用に初期位置を保持
	Vector3 mInitPosition;
	//!ダメージ時のエフェクト
	UIDisappearingQuad mDamageEffect;
};

/* End of File *****************************************************/