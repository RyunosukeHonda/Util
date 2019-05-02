/**
* @file ObjectManager.h
* @brief IObject�Ǘ��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "BASE.h"
#include "EntityManager.h"

class IObject;
class IRenderer;

/**
*	IObject�Ǘ��N���X	
*	�X�V�Ȃǂ̏������K�v�Ȃ��I�u�W�F�N�g�̕`����s���܂�
*/
class ObjectManager
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	ObjectManager();
	
	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~ObjectManager();

	/**
	* @fn
	* �I�u�W�F�N�g�ǉ�
	* @param (pObj) �ǉ�����v�f�̃|�C���^
	*/
	void add(IObject* pObj);

	/**
	* @fn
	* �S�v�f�`��
	* @param (renderer) �����_���[ 
	*/
	void draw(IRenderer& renderer);

	/**
	* @fn
	* �S�v�f�폜
	*/
	void clear();

private:
	EntityManager<IObject*> mObjList;
};

/* End of File *****************************************************/