/**
* @file Bullet.h
* @brief 弾クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "ACharacter.h"
#include "SphereCollider.h"
#include "OBJStaticMeshRenderDesc.h"

/**
*	弾クラス
*/
class Bullet : public ACharacter, public SphereCollider
{
	///定数
private:
	//!弾速
	static const float BULLET_SPEED;

public:
	/**
	* @fn
	* コンストラクタ
	* @param (pos) 生成位置
	* @param (dir) 進行方向ベクトル
	*/
	Bullet(const Vector3& pos, const Vector3& dir);

	/**
	 * @fn
	 * デストラクタ
	 */
	~Bullet();

	// ACharacter を介して継承されました
	virtual void init() override;
	virtual void fixedUpdate(float dt) override;
	virtual void draw(IRenderer & renderer) override;

	// ASphereCollider を介して継承されました
	virtual void onCollisionEnter(ACollider* other) override;

private:
	//!モデル描画記述子
	OBJStaticMeshRenderDesc mDesc;
};

/* End of File *****************************************************/