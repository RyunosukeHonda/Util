/**
* @file TitleSequencer.h
* @brief �^�C�g���V�[�P���T�[�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "StateMachineTemplate.h"
#include "ITitleState.h"

/**
*	�^�C�g���V�[�P���T�[�N���X
*	�^�C�g���V�[���̗�����Ǘ�
*/
class TitleSequencer : public StateMachineTemplate<ETitleState, ITitleState>
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	TitleSequencer();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~TitleSequencer();

	/**
	* @fn
	* ���݂̃X�e�[�g���X�V����
	* @param (input) ���͋@�\
	*/
	void update(IInput& input);

	/**
	* @fn
	* ���݂̃X�e�[�g��`��
	* @param (renderer) �����_���[
	*/
	void draw(IRenderer& renderer);
};

/* End of File *****************************************************/