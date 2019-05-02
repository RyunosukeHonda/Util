/**
* @file IGameDevice.h
* @brief ゲームデバイス仲介インターフェース
* @author Ryunosuke Honda.
*/
#pragma once

#include <combaseapi.h>

//レンダラーインタフェース
class IRenderer;

//入力インタフェース
class IInput;

/**
*	ゲームデバイス仲介インターフェース
*/
class IGameDevice
{
public:
	/**
	* @fn
	* 仮想デストラクタ
	*/
	virtual ~IGameDevice(){}

	/**
	* @fn
	* レンダラー取得
	*/
	virtual IRenderer& renderer() = 0;

	/**
	* @fn
	* 入力クラス取得
	*/
	virtual IInput& input() = 0;
};

/****** End of File *****************************************************/