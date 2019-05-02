/**
* @file UtilMacro.h
* @brief 汎用できるマクロをまとめておくファイル
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @def COPY_PROTECTED
* 設定したクラスのコピーを禁止するマクロ
* @param (_P_TYPE) コピーを禁止したいクラス
*/
#define COPY_PROTECTED(_P_TYPE)				\
private:									\
_P_TYPE(const _P_TYPE& other);				\
_P_TYPE& operator = (const _P_TYPE& other);

/* End of File *****************************************************/