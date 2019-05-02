/**
* @file PlayableCharacterManager.h
* @brief ����\�L�����N�^�[�Ǘ��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "EntityManager.h"

class APlayableCharacter;
class IInput;
class IRenderer;

/**
*	����\�L�����N�^�[�Ǘ��N���X
*/
class PlayableCharacterManager
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	PlayableCharacterManager();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~PlayableCharacterManager();

	/**
	* @fn
	* �L�����N�^�[�ǉ�
	* @param (pc) �ǉ�����L�����N�^�[�̃|�C���^
	*/
	void add(APlayableCharacter* pc);

	/**
	* @fn
	* ���X�g�N���A
	*/
	void clear();

	/**
	* @fn
	* �v�f������
	*/
	void init();

	/**
	* @fn
	* �v�f�X�V
	*/
	void update(IInput& input);

	/**
	* @fn
	* �v�f�x���X�V
	*/
	void lateUpdate(IInput& input);

	/**
	* @fn
	* �v�f�x���X�V
	*/
	void fixedUpdate(float dt);

	/**
	* @fn
	* �v�f�`��
	* @param (renderer) �����_���[
	*/
	void draw(IRenderer& renderer);

	/**
	* @fn
	* �`����s
	* @param (renderer) �����_���[
	*/
	void renderExecute(IRenderer& renderer);

	/**
	* @fn
	* �v���C���[���������o�Ɉڍs������ 
	*/
	void gameSet();

private:
	//!����L�����N�^�[���X�g
	EntityManager<APlayableCharacter*> mPlayableCharacterList;
	//!�V�[���I���t���O�E�v���C���[�̒N�������S������V�[���I��
	PROPERTY_READONLY(bool, IsEnd);
};

/* End of File *****************************************************/