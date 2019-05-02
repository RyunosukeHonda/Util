/**
* @file SphereCSBuffer
* @brief 境界球判定を行うコンピュートシェーダーへの情報受け渡しバッファ
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	境界球判定を行うコンピュートシェーダーへの情報受け渡しバッファ
*/
struct SphereCSBuffer
{
	///４次元ベクトルのxyz成分に座標を、
	///w成分に半径を格納することで
	///データの受け渡し量を減らす。
	//!球１の情報・w成分に半径
	Vector4 sph1;
	//!球２の情報・w成分に半径
	Vector4 sph2;
};

/****** End of File *****************************************************/
