/**
* @file PropertyMacro.h
* @brief プロパティを自動生成するマクロの定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @def PROPERTY_READWRITE
* 読み取り、書き込み可能なプロパティの生成
* @param (_P_TYPE) 生成するプロパティの型
* @param (_P_MEMBER) 生成される変数名・m##_P_MEMBERの名前になります
*/
#define PROPERTY_READWRITE( _P_TYPE ,_P_MEMBER )										\
protected : _P_TYPE m##_P_MEMBER ;														\
public :																				\
__declspec (property ( get= get##_P_MEMBER , put= set##_P_MEMBER )) _P_TYPE _P_MEMBER ;	\
const _P_TYPE & get##_P_MEMBER () const { return m##_P_MEMBER ; }									\
void set##_P_MEMBER (const _P_TYPE &value ){ m##_P_MEMBER = value ; }

/**
* @def PROPERTY_READONLY
* 読み取り可能、書き込み不可能なプロパティの生成
* @param (_P_TYPE) 生成するプロパティの型
* @param (_P_MEMBER) 生成される変数名・m##_P_MEMBERの名前になります
*/
#define PROPERTY_READONLY( _P_TYPE ,_P_MEMBER )						\
protected : _P_TYPE m##_P_MEMBER ;									\
public :															\
__declspec (property ( get= get##_P_MEMBER )) _P_TYPE _P_MEMBER ;	\
const _P_TYPE & get##_P_MEMBER () const { return m##_P_MEMBER ; }								

/**
* @def PROPERTY_WRITEONLY
* 書き込み可能、読み取り不可能なプロパティの生成
* @param (_P_TYPE) 生成するプロパティの型
* @param (_P_MEMBER) 生成される変数名・m##_P_MEMBERの名前になります
*/
#define PROPERTY_WRITEONLY( _P_TYPE ,_P_MEMBER )						\
protected : _P_TYPE m##_P_MEMBER ;										\
public :																\
__declspec (property ( put= set##_P_MEMBER )) _P_TYPE _P_MEMBER ;		\
void set##_P_MEMBER (const _P_TYPE &value ){ m##_P_MEMBER = value ; }

/**
* @def PROPERTY_READONLY_POINTER
* 読み取り可能、書き込み不可能なプロパティの生成・ポインター変数用
* @param (_P_TYPE) 生成するプロパティの型
* @param (_P_MEMBER) 生成される変数名・mp##_P_MEMBERの名前になります
*/
#define PROPERTY_READONLY_POINTER( _P_TYPE ,_P_MEMBER )				\
protected : _P_TYPE mp##_P_MEMBER ;									\
public :															\
__declspec (property ( get= get##_P_MEMBER )) _P_TYPE _P_MEMBER ;	\
_P_TYPE get##_P_MEMBER () const{ return mp##_P_MEMBER ; }

/**
* @def PROPERTY_WRITEONLY
* 書き込み可能、読み取り不可能なプロパティの生成
* @param (_P_TYPE) 生成するプロパティの型
* @param (_P_MEMBER) 生成される変数名・m##_P_MEMBERの名前になります
*/
#define PROPERTY_WRITEONLY_POINTER( _P_TYPE ,_P_MEMBER )						\
protected : _P_TYPE mp##_P_MEMBER ;										\
public :																\
__declspec (property ( put= set##_P_MEMBER )) _P_TYPE _P_MEMBER ;		\
void set##_P_MEMBER (_P_TYPE value ){ mp##_P_MEMBER = value ; }

/**
* @def PROPERTY_READWRITE_ADDFUNC
* 読み取り、書き込み可能なプロパティの生成・getter,setterに独自関数をもたせたい場合に使用
* @param (_P_TYPE) 生成するプロパティの型
* @param (_P_MEMBER) 生成される変数名・m##_P_MEMBERの名前になります
* @param (_GETFUNC) getterが呼ばれた際に値を返す直前に呼ぶ関数を指定
* @param (_SETFUNC) setterが呼ばれた際に値を設定する直前に呼ぶ関数を指定
*/
#define PROPERTY_READWRITE_ADDFUNC( _P_TYPE, _P_MEMBER, _GETFUNC, _SETFUNC )										\
protected : _P_TYPE m##_P_MEMBER ;														\
public :																				\
__declspec (property ( get= get##_P_MEMBER , put= set##_P_MEMBER )) _P_TYPE _P_MEMBER ;	\
_P_TYPE & get##_P_MEMBER ()																\
{																						\
	_GETFUNC ();																		\
	return m##_P_MEMBER ;																\
}																						\
void set##_P_MEMBER (const _P_TYPE &value )												\
{																							\
	_SETFUNC (value);																	\
}					

/**
* @def PROPERTY_READWRITE_ADDSETTER
* 読み取り、書き込み可能なプロパティの生成・setterに独自関数をもたせたい場合に使用
* @param (_P_TYPE) 生成するプロパティの型
* @param (_P_MEMBER) 生成される変数名・m##_P_MEMBERの名前になります
* @param (_SETFUNC) setter(関数名)を指定・引数(const _P_TYPE & value)が必須
*/
#define PROPERTY_READWRITE_ADDSETTER( _P_TYPE, _P_MEMBER, _SETFUNC )										\
protected : _P_TYPE m##_P_MEMBER ;														\
public :																				\
__declspec (property ( get= get##_P_MEMBER , put= set##_P_MEMBER )) _P_TYPE _P_MEMBER ;	\
const _P_TYPE & get##_P_MEMBER () const															\
{																						\
	return m##_P_MEMBER ;																\
}																						\
void set##_P_MEMBER (const _P_TYPE &value )												\
{																						\
	_SETFUNC (value);																	\
}				

/* End of File *****************************************************/