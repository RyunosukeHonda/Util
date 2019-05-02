/**
* @file Status.h
* @brief �X�e�[�^�X�N���X��`�t�@�C��
* �̗͂ȂǃL�����N�^�[�Ɏ����������l�Ƃ��̐U�镑��������
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

class IRenderer;

/**
*	�X�e�[�^�X�N���X
*/
class Status : public CElement
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (hp) �̗�
	*/
	Status(int hp);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~Status();

	/**
	* @fn
	* �X�e�[�^�X������
	*/
	void init();

	/**
	* @fn
	* �_���[�W��^����(HP�����炷)
	* @param (damage) �^����_���[�W��
	*/
	void damage(const int& damage);

	/**
	* @fn
	* ���S���Ă��邩����
	* @return ���S���Ă����true
	*/
	bool isDead() const;

	/**
	* @fn
	* ���S���Ă��邩����
	* @return ���S���Ă����true
	*/
	void draw(IRenderer& renderer) const;

private:
	//!�q�b�g�|�C���g
	int mHP;
	//!�q�b�g�|�C���g�ő�l�E�������p�ɕۑ�
	int mMaxHP;
};

/* End of File *****************************************************/