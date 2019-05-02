/**
* @file APlayableCharacter.h
* @brief ����\�Ȓ��ۃL�����N�^�[�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IObject.h"
#include "Status.h"

class IInput;

/**
*	����\�Ȓ��ۃL�����N�^�[�N���X
*/
class APlayableCharacter : public IObject
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (hp) �̗�
	*/
	APlayableCharacter(int hp);

	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~APlayableCharacter() {}

	/**
	* @fn
	* ������
	*/
	virtual void init() = 0;

	/**
	* @fn
	* �X�V����
	*/
	virtual void update(IInput& input) = 0;

	/**
	* @fn
	* update��ɏ��������X�V����
	*/
	virtual void lateUpdate(IInput& input) = 0;

	/**
	* @fn
	* 60FPS�����X�V
	*/
	virtual void fixedUpdate(float dt) = 0;

	/**
	* @fn
	* �`����s
	* @brief ���̃Q�[���ł̓v���C���[�̖ڐ������̂܂܃J�����ɂȂ邽�߁A
	* �ێ����Ă���J�����ڐ��ŕ`������s���Ă��炤
	* @param (renderer) �����_���[
	*/
	virtual void renderExecute(IRenderer& renderer) = 0;

	/**
	* @fn
	* ���S���Ă��邩
	*/
	virtual bool isDead() const;

	/**
	* @fn
	* �Q�[������������
	*/
	virtual void gameSet() = 0;

protected:
	//!�X�e�[�^�X
	Status mStatus;
};

/* End of File *****************************************************/