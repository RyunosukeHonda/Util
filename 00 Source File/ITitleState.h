/**
* @file ITitleState.h
* @brief �^�C�g����ԃC���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

#include "IState.h"
#include "ETitleState.h"

class IInput;
class IRenderer;

/**
*	�^�C�g����ԃC���^�[�t�F�[�X
*/
class ITitleState : public IState<ETitleState>
{
public:
	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~ITitleState() {}

	/**
	* @fn
	* �X�V
	* @param (input) ���͋@�\
	*/
	virtual void update(IInput& input) = 0;

	/**
	* @fn
	* �`��
	* @param (renderer) �����_���[
	*/
	virtual void draw(IRenderer& renderer) = 0;
};

/* End of File *****************************************************/