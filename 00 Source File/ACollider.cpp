/**
* @file ACollider.cpp
* @brief 抽象コライダー実装ファイル
* @author Ryunosuke Honda.
*/
#include "ACollider.h"

ACollider::ACollider(const ERigidType& type) :
	base(type),
	mInfo()
{
}

ACollider::~ACollider()
{
	//情報のクリアのみ。実体の削除は行いません
	mInfo.clear();
}

void ACollider::result(ACollider * other, bool isCol)
{
	//衝突情報保管マップにコライダーが登録されていなければ
	if (mInfo.count(other) == 0)
	{
		//衝突(isCol)を保管
		mInfo[other] = isCol;
		//衝突していればEnterを呼び、リターン
		if (isCol)
			onCollisionEnter(other);
		return;
	}

	//以下は衝突したかどうかで分岐
	//衝突していた場合
	if (isCol)
	{
		//前フレームの衝突情報で呼び出す関数を選択
		//前フレームで衝突していなかった
		if (mInfo[other] == false)
		{
			//衝突(true)を保管
			mInfo[other] = true;
			//Enter,Stayを呼び出しリターン
			onCollisionEnter(other);
			onCollisionStay(other);
			return;
		}

		//前フレームで衝突していたら
		//Stayを呼び出しリターン(保管の必要なし)
		onCollisionStay(other);
		return;
	}

	//衝突していなかった場合
	//前フレームで衝突していればExitを呼び出す
	if (mInfo[other] == true)
	{
		//衝突情報(false)を保管
		mInfo[other] = false;
		onCollisionExit(other);
	}

	//***************
	//ここにたどり着いていたら
	//前フレームで衝突していない、
	//今フレームも衝突していないということで
	//処理は特になし
	//***************
}

bool ACollider::isInvalid() const
{
	//レイヤー列挙型の終端以上の数値なら不正
	return static_cast<unsigned int>(mLayer) > static_cast<unsigned int>(ELayer::LAYER_END);
}

/* End of File *****************************************************/