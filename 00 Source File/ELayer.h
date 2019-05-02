/**
* @file ELayer.h
* @brief レイヤー列挙型・描画、衝突判定時などのTransformの分類に使用
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @enum ELayer
* レイヤー列挙型
*/
enum ELayer : unsigned int
{
	//!デフォルト、特に設定が必要ない場合・レイヤーマスクに使用するため１で初期化
	DEFAULT = 1,
	//!チーム1・プレイヤー１に適用
	TEAM1,
	//!チーム２・プレイヤー２に適用
	TEAM2,
	//!チーム１の銃弾・チーム２と衝突
	BULLET1,
	//!チーム２の銃弾・チーム１と衝突
	BULLET2,
	//!終端・これ以上の数値はエラー
	LAYER_END,
};

/****** End of File *****************************************************/
