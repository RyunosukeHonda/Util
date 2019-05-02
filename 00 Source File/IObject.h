/**
* @file AObject.h
* @brief オブジェクトインターフェース
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

class IRenderer;

/**
*	オブジェクトインターフェース・オブジェクトは最低限の機能として描画機能を持つ
*/
class IObject
{
public:
	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~IObject() {}

	/**
	* @fn
	* 描画
	*/
	virtual void draw(IRenderer& renderer) = 0;
};

/* End of File *****************************************************/