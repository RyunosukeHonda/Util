/**
* @file PlayableCharacterManager.h
* @brief 操作可能キャラクター管理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "EntityManager.h"

class APlayableCharacter;
class IInput;
class IRenderer;

/**
*	操作可能キャラクター管理クラス
*/
class PlayableCharacterManager
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	PlayableCharacterManager();

	/**
	 * @fn
	 * デストラクタ
	 */
	~PlayableCharacterManager();

	/**
	* @fn
	* キャラクター追加
	* @param (pc) 追加するキャラクターのポインタ
	*/
	void add(APlayableCharacter* pc);

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
	* 要素更新
	*/
	void update(IInput& input);

	/**
	* @fn
	* 要素遅延更新
	*/
	void lateUpdate(IInput& input);

	/**
	* @fn
	* 要素遅延更新
	*/
	void fixedUpdate(float dt);

	/**
	* @fn
	* 要素描画
	* @param (renderer) レンダラー
	*/
	void draw(IRenderer& renderer);

	/**
	* @fn
	* 描画実行
	* @param (renderer) レンダラー
	*/
	void renderExecute(IRenderer& renderer);

	/**
	* @fn
	* プレイヤーを決着演出に移行させる 
	*/
	void gameSet();

private:
	//!操作キャラクターリスト
	EntityManager<APlayableCharacter*> mPlayableCharacterList;
	//!シーン終了フラグ・プレイヤーの誰かが死亡したらシーン終了
	PROPERTY_READONLY(bool, IsEnd);
};

/* End of File *****************************************************/