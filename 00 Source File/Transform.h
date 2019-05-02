/**
* @file Transform.h
* @brief 3次元トランスフォーム情報クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "ETag.h"
#include "ELayer.h"
#include "EntityManager.h"

/**
*	3次元トランスフォーム情報クラス
*	オブジェクトの位置、回転、スケールの他
*	タグやレイヤー、向きなどを扱うクラス
*/
class Transform : public CElement
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	Transform();

	/**
	 * @fn
	 * デストラクタ
	 */
	virtual ~Transform();

	/**
	* @fn
	* トランスフォーム情報をワールド座標系に変換して引数に格納する
	* @param (world) ワールド座標を格納するMatrixポインタ
	*/
	void makeWorld(Matrix4x4* world);

	/**
	* @fn
	* 親オブジェクトの設定
	* @param (parent) 親オブジェクトのトランスフォーム
	* @detail 同時に親オブジェクトの子配列に登録する
	*/
	void setParent(Transform* parent);

	/**
	* @fn
	* 親オブジェクト取得
	* @return 親トランスフォームのポインタ
	*/
	Transform* getParent();

	/**
	* @fn
	* 子オブジェクト取得
	* @param (index) 子配列上のインデックス
	* @return 子トランスフォームのポインタ
	*/
	//Transform* getChild(int index);

	/**
	* @fn
	* トランスフォームのルートを取得
	* @return ルート(一番上の階層)
	*/
	Transform* getRoot();

	/**
	* @fn
	* 自身がトランスフォームのルートかどうかを取得
	* @return ルートならtrue
	*/
	bool isRoot();

	void lookAt(const Vector3& target);

private:
	///以下、値設定時に対応した値を同時に更新する関数

	void setChild(Transform* child);

	void calcLocalPosition(const Vector3& localPosition);

	void calcPosition(const Vector3& position);

	void calcLocalEulerAngle(const Vector3& euler);

	void calcEulerAngle(const Vector3& euler);

	void calcLocalScale(const Vector3& scale);

	void calcScale(const Vector3& localScale);

	void calcRotation();

	void calcDirection();

	void updateChildren();

	///以下プロパティ

	//!ローカル位置
	PROPERTY_READWRITE_ADDSETTER(Vector3, LocalPosition, calcPosition);
	//!ローカルの向き(オイラー角、Degreeで定義)
	PROPERTY_READWRITE_ADDSETTER(Vector3, LocalEulerAngle, calcEulerAngle);
	//!ローカルスケール(（1,1,1）で初期化)
	PROPERTY_READWRITE_ADDSETTER(Vector3, LocalScale, calcScale);
	//!ワールド位置
	PROPERTY_READWRITE_ADDSETTER(Vector3, Position, calcLocalPosition);
	//!ワールド向き(オイラー角、Degreeで定義)
	PROPERTY_READWRITE_ADDSETTER(Vector3, EulerAngle, calcLocalEulerAngle);
	//!ワールドスケール
	PROPERTY_READWRITE_ADDSETTER(Vector3, Scale, calcLocalScale);
	//!ワールドローテーション(行列で保持)
	PROPERTY_READONLY(Matrix4x4, Rotation);
	//!前方向ベクトル
	PROPERTY_READONLY(Vector3, Forward);
	//!上方向ベクトル
	PROPERTY_READONLY(Vector3, Up);
	//!右方向ベクトル
	PROPERTY_READONLY(Vector3, Right);
	//!オブジェクトタグ
	PROPERTY_READWRITE(ETag, Tag);
	//!オブジェクトレイヤー
	PROPERTY_READWRITE(ELayer, Layer);

private:
	//!親オブジェクトのトランスフォーム
	Transform* mParent;
	//!子オブジェクト配列
	EntityManager<Transform*, NoDestroy> mChildren;
};

/* End of File *****************************************************/