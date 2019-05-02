/**
* @file UtilMacro.h
* @brief �ėp�ł���}�N�����܂Ƃ߂Ă����t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @def COPY_PROTECTED
* �ݒ肵���N���X�̃R�s�[���֎~����}�N��
* @param (_P_TYPE) �R�s�[���֎~�������N���X
*/
#define COPY_PROTECTED(_P_TYPE)				\
private:									\
_P_TYPE(const _P_TYPE& other);				\
_P_TYPE& operator = (const _P_TYPE& other);

/* End of File *****************************************************/