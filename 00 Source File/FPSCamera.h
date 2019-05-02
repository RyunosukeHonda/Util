/**
* @file FPSCamera.h
* @brief FPSカメラクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Camera.h"

/**
*	FPSカメラクラス
*/
class FPSCamera : public Camera
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 * @param (follow) 追従対象
	 */
	FPSCamera(Transform* follow);

	/**
	 * @fn
	 * デストラクタ
	 */
	~FPSCamera();

	/**
	* @fn
	* 初期化
	*/
	void init(const Vector2& initRotateAmount);
	
	virtual void update() override;

protected:
	//!カメラの回転量
	PROPERTY_READWRITE(Vector2, RotateAmount);
	//!視線となり追従するオブジェクトのトランスフォーム
	Transform* mpObject;
	//!追従オブジェクトとの差分
	PROPERTY_WRITEONLY(Vector3, Offset);

private:
	using base = Camera;
};

/* End of File *****************************************************/