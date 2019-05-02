/**
* @file PropertyMacro.h
* @brief �v���p�e�B��������������}�N���̒�`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @def PROPERTY_READWRITE
* �ǂݎ��A�������݉\�ȃv���p�e�B�̐���
* @param (_P_TYPE) ��������v���p�e�B�̌^
* @param (_P_MEMBER) ���������ϐ����Em##_P_MEMBER�̖��O�ɂȂ�܂�
*/
#define PROPERTY_READWRITE( _P_TYPE ,_P_MEMBER )										\
protected : _P_TYPE m##_P_MEMBER ;														\
public :																				\
__declspec (property ( get= get##_P_MEMBER , put= set##_P_MEMBER )) _P_TYPE _P_MEMBER ;	\
const _P_TYPE & get##_P_MEMBER () const { return m##_P_MEMBER ; }									\
void set##_P_MEMBER (const _P_TYPE &value ){ m##_P_MEMBER = value ; }

/**
* @def PROPERTY_READONLY
* �ǂݎ��\�A�������ݕs�\�ȃv���p�e�B�̐���
* @param (_P_TYPE) ��������v���p�e�B�̌^
* @param (_P_MEMBER) ���������ϐ����Em##_P_MEMBER�̖��O�ɂȂ�܂�
*/
#define PROPERTY_READONLY( _P_TYPE ,_P_MEMBER )						\
protected : _P_TYPE m##_P_MEMBER ;									\
public :															\
__declspec (property ( get= get##_P_MEMBER )) _P_TYPE _P_MEMBER ;	\
const _P_TYPE & get##_P_MEMBER () const { return m##_P_MEMBER ; }								

/**
* @def PROPERTY_WRITEONLY
* �������݉\�A�ǂݎ��s�\�ȃv���p�e�B�̐���
* @param (_P_TYPE) ��������v���p�e�B�̌^
* @param (_P_MEMBER) ���������ϐ����Em##_P_MEMBER�̖��O�ɂȂ�܂�
*/
#define PROPERTY_WRITEONLY( _P_TYPE ,_P_MEMBER )						\
protected : _P_TYPE m##_P_MEMBER ;										\
public :																\
__declspec (property ( put= set##_P_MEMBER )) _P_TYPE _P_MEMBER ;		\
void set##_P_MEMBER (const _P_TYPE &value ){ m##_P_MEMBER = value ; }

/**
* @def PROPERTY_READONLY_POINTER
* �ǂݎ��\�A�������ݕs�\�ȃv���p�e�B�̐����E�|�C���^�[�ϐ��p
* @param (_P_TYPE) ��������v���p�e�B�̌^
* @param (_P_MEMBER) ���������ϐ����Emp##_P_MEMBER�̖��O�ɂȂ�܂�
*/
#define PROPERTY_READONLY_POINTER( _P_TYPE ,_P_MEMBER )				\
protected : _P_TYPE mp##_P_MEMBER ;									\
public :															\
__declspec (property ( get= get##_P_MEMBER )) _P_TYPE _P_MEMBER ;	\
_P_TYPE get##_P_MEMBER () const{ return mp##_P_MEMBER ; }

/**
* @def PROPERTY_WRITEONLY
* �������݉\�A�ǂݎ��s�\�ȃv���p�e�B�̐���
* @param (_P_TYPE) ��������v���p�e�B�̌^
* @param (_P_MEMBER) ���������ϐ����Em##_P_MEMBER�̖��O�ɂȂ�܂�
*/
#define PROPERTY_WRITEONLY_POINTER( _P_TYPE ,_P_MEMBER )						\
protected : _P_TYPE mp##_P_MEMBER ;										\
public :																\
__declspec (property ( put= set##_P_MEMBER )) _P_TYPE _P_MEMBER ;		\
void set##_P_MEMBER (_P_TYPE value ){ mp##_P_MEMBER = value ; }

/**
* @def PROPERTY_READWRITE_ADDFUNC
* �ǂݎ��A�������݉\�ȃv���p�e�B�̐����Egetter,setter�ɓƎ��֐��������������ꍇ�Ɏg�p
* @param (_P_TYPE) ��������v���p�e�B�̌^
* @param (_P_MEMBER) ���������ϐ����Em##_P_MEMBER�̖��O�ɂȂ�܂�
* @param (_GETFUNC) getter���Ă΂ꂽ�ۂɒl��Ԃ����O�ɌĂԊ֐����w��
* @param (_SETFUNC) setter���Ă΂ꂽ�ۂɒl��ݒ肷�钼�O�ɌĂԊ֐����w��
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
* �ǂݎ��A�������݉\�ȃv���p�e�B�̐����Esetter�ɓƎ��֐��������������ꍇ�Ɏg�p
* @param (_P_TYPE) ��������v���p�e�B�̌^
* @param (_P_MEMBER) ���������ϐ����Em##_P_MEMBER�̖��O�ɂȂ�܂�
* @param (_SETFUNC) setter(�֐���)���w��E����(const _P_TYPE & value)���K�{
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