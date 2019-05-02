/**
* @file StateMachineTemplate.h
* @brief �X�e�[�g�p�^�[���e���v���[�g�N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "Manager.h"
#include "IState.h"

/**
*	�X�e�[�g�p�^�[���e���v���[�g�N���X
*	��Ԃ̓o�^�A�I�����̏�ԕύX�����s��
*	�X�e�[�g�I�������h���N���X�ŌĂяo���Ȃ���΂Ȃ�Ȃ��̂Œ���
*	(K) �X�e�[�g�}�b�v�̃L�[�E�񋓌^�𐄏�
*	(V = IState) �o�^����X�e�[�g�EIState���p�����Ă��邱�Ƃ�����
*/
template<class K, class V = IState<K>>
class StateMachineTemplate : public Manager<K, V>
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	StateMachineTemplate() {}

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	virtual ~StateMachineTemplate() {}

	/*
	* @fn
	* ������
	* @brief �w�肵����ԂɕύX����
	* change���Ă΂��͍̂D�܂����Ȃ�����
	* �ŏ��̈�x�̂ݗ��p�҂ɌĂяo���Ă��炤
	* @param (name)  �L�[�F�X�e�[�g��
	*/
	void initState(const K name)
	{
		change(name);
	}

	bool isEnd()
	{

	}

protected:
	/*
	* @fn
	* �X�e�[�g�ύX
	* @param (name)  �L�[�F�X�e�[�g��
	* @brief �A�z�z�񂩂�����̃V�[�������o���A
	*        ���݂̃V�[���ɓo�^����
	*/
	void change(K name)
	{
		if (mCurrentState != nullptr)
		{
			//�X�e�[�g�I��������
			mCurrentState->shutdown();
		}
		//���̃X�e�[�g���擾���A������
		mCurrentState = get(name);
		mCurrentState->init();
	}

	/*
	* @fn
	* �X�e�[�g�I���`�F�b�N
	* @brief �h�����update�ȂǂŌĂяo���Ȃ��ƃX�e�[�g���ύX����Ȃ��̂Œ���
	*/
	void stateEndCheck()
	{
		//�V�[�����I�����Ă����玟�̃V�[���֑J��
		if (mCurrentState->isEnd())
		{
			change(mCurrentState->next());
		}
	}

protected:
	//!�v�f�|�C���^����
	using IStatePointer = ProductPointer;
	//!���݃X�e�[�g
	IStatePointer mCurrentState;
};

/* End of File *****************************************************/