/**
* @file GameMainSequencer.h
* @brief �Q�[�����C���V�[���V�[�P���T�[�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "StateMachineTemplate.h"
#include "IGameMainState.h"

/**
*	�Q�[�����C���V�[���V�[�P���T�[�N���X
*	���C��(�o�g��)�V�[���̗�����Ǘ�
*/
class GameMainSequencer : public StateMachineTemplate<EGameMainState, IGameMainState>
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	GameMainSequencer();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~GameMainSequencer();

	/**
	* @fn
	* ���݂̃X�e�[�g���X�V����
	* @param (input) ���͋@�\
	*/
	void update(IInput& input);

	/**
	* @fn
	* FPS60�����X�V�E��������̏������L�q
	* @param (dt) �t���[���΍�����
	*/
	void fixedUpdate(float dt) ;

	/**
	* @fn
	* �x���X�V�Eupdate��肠�ƂɎ��s�������������L�q
	* @param (input) ���̓C���^�[�t�F�[�X
	*/
	void lateUpdate(IInput& input);

	/**
	* @fn
	* ���݂̃X�e�[�g��`��
	* @param (renderer) �����_���[
	*/
	void draw(IRenderer& renderer);
};

/* End of File *****************************************************/