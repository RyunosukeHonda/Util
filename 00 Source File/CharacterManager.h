/**
* @file CharacterManager.h
* @brief キャラクター管理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "EntityManager.h"
#include "IAddable.h"

class IRenderer;
class ACharacter;

/**
*	キャラクター管理クラス
*/
class CharacterManager : public IAddable<ACharacter>
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	CharacterManager();

	/**
	 * @fn
	 * デストラクタ
	 */
	~CharacterManager();

	/**
	* @fn
	* キャラクター追加
	* @param (npc) 追加するキャラクターのポインタ
	*/
	virtual void add(ACharacter* npc) override;

	/**
	* @fn
	* リストクリア
	*/
	void clear();

	/**
	* @fn
	* 要素初期化
	*/
	void init();

	/**
	* @fn
	* 要素更新・60FPS
	*/
	void fixedUpdate(float dt);

	/**
	* @fn
	* 要素描画
	*/
	void draw(IRenderer& renderer);

private:
	//!キャラクターリスト
	EntityManager<ACharacter*, NoDestroy> mCharacterList;
};

/* End of File *****************************************************/