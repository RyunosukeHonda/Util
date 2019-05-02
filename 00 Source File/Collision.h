/**
* @file Collision.h
* @brief �����蔻��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Singleton.h"

struct ID3D11Device;
struct ID3D11DeviceContext;

class SphereCollider;
class PlaneCollider;

class SphereXSphereJudge;

/**
*	�����蔻��N���X�E�V���O���g���Ŏg�p
*	�N���X��剻��}�����邽�ߌv�Z���̂͊e�@�\�N���X���s��
*/
class Collision : public Singleton<Collision>
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	Collision();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~Collision();

	/**
	* @fn
	* �@�\�������E�f�o�C�X�̕ێ��Ɗe�v�Z�@�\�̏�����
	* @param (pDevice) �f�o�C�X�|�C���^
	* @param (pDeviceContext) �f�o�C�X�R���e�L�X�g�|�C���^
	* @detail ��x�̂݌Ăяo���Ώ\��
	*/
	void init(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);

	/**
	* @fn
	* �Փ˔���
	* @brief ���E�����m�𔻒�
	* @param (sph1) ���E���R���C�_�[�P
	* @param (sph2) ���E���R���C�_�[�Q
	* @return �Փ˂��Ă����true
	* @detail �Փ˂��Ă����ꍇ�A���݂��̏Փˎ��������Ăяo����܂�
	*/
	void collision(SphereCollider* sph1, SphereCollider* sph2);

	/**
	* @fn
	* �Փ˔���
	* @brief Sphere��Plane�𔻒�
	* @param (sph) ���E���R���C�_�[
	* @param (pln) ���ʃR���C�_�[
	* @return �Փ˂��Ă����true
	* @detail �Փ˂��Ă����ꍇ�A���݂��̏Փˎ��������Ăяo����܂�
	*/
	void collision(SphereCollider* sph, PlaneCollider* pln);

	/**
	* @fn
	* �Փ˔���
	* @brief ���ʓ��m�𔻒�
	* @param (pln1) ���ʃR���C�_�[�P
	* @param (pln2) ���ʃR���C�_�[�Q
	* @return �Փ˂��Ă����true
	* @detail �Փ˂��Ă����ꍇ�A���݂��̏Փˎ��������Ăяo����܂�
	*/
	void collision(PlaneCollider* pln1, PlaneCollider* pln2);

private:
	//!DirectX�f�o�C�X�|�C���^�E�o�b�t�@�̍쐬�Ɏg�p
	ID3D11Device* mpDevice;
	//!DirectX�f�o�C�X�R���e�L�X�g�|�C���^�E�R���s���[�g�V�F�[�_�[�̐ݒ�ȂǂɎg�p
	ID3D11DeviceContext* mpDeviceContext;
	//!�����m�̏Փˌv�Z�N���X
	SphereXSphereJudge* mpSphXSph;
};

/* End of File *****************************************************/