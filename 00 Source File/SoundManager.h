/**
* @file SoundManager.h
* @brief 音リソース管理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "Manager.h"
#include "SoundID.h"
#include "Sound.h"
#include "Singleton.h"

/**
*	音リソース管理クラス(シングルトン)
*/
class SoundManager :
	private Manager<SoundID, Sound>,
	public Singleton<SoundManager>
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	SoundManager();

	/**
	 * @fn
	 * デストラクタ
	 */
	~SoundManager();

	/**
	* @fn
	* サウンド読み込み
	* @param (id) リソース管理番号
	* @param (fileName) 読み込むファイル名
	*/
	void load(const SoundID &id, char* fileName);

	/**
	* @fn
	* サウンド再生
	* @param (id) リソース管理番号
	* @param (isLoop) ループ再生するか
	*/
	void play(const SoundID &id, bool isLoop);

	/**
	* @fn
	* サウンド停止
	* @param (id) リソース管理番号
	*/
	void stop(const SoundID& id);
	
	/**
	* @fn
	* サウンド削除
	* @param (id) リソース管理番号
	*/
	void remove(const SoundID& id);

	/**
	* @fn
	* サウンド全削除
	*/
	void clear();

private:
	/**
	* @fn
	* 初期化
	* @return 成功したかどうか
	*/
	void init();

	//!XAudio2機能インターフェイス
	IXAudio2* mpXAudio2;
	//!マスタリングボイス
	IXAudio2MasteringVoice* mpMasteringVoice;
};

/* End of File *****************************************************/