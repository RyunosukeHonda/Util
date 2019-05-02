/**
* @file CharacterManager.h
* @brief �L�����N�^�[�Ǘ��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "EntityManager.h"
#include "IAddable.h"

class IRenderer;
class ACharacter;

/**
*	�L�����N�^�[�Ǘ��N���X
*/
class CharacterManager : public IAddable<ACharacter>
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	CharacterManager();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~CharacterManager();

	/**
	* @fn
	* �L�����N�^�[�ǉ�
	* @param (npc) �ǉ�����L�����N�^�[�̃|�C���^
	*/
	virtual void add(ACharacter* npc) override;

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
	* �v�f�X�V�E60FPS
	*/
	void fixedUpdate(float dt);

	/**
	* @fn
	* �v�f�`��
	*/
	void draw(IRenderer& renderer);

private:
	//!�L�����N�^�[���X�g
	EntityManager<ACharacter*, NoDestroy> mCharacterList;
};

/* End of File *****************************************************/