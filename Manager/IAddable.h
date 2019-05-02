/**
* @file IAddable.h
* @brief �Ǘ��v�f�ǉ��@�\����C���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once

/**
*	�Ǘ��v�f�ǉ��@�\����C���^�[�t�F�[�X
*/
template<class T>
class IAddable
{
public:
	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	virtual ~IAddable() {};

	/**
	* @fn
	* �v�f�ǉ�
	* @param (value) �ǉ�����v�f�̃|�C���^
	*/
	virtual void add(T* value) = 0;
};

/* End of File *****************************************************/