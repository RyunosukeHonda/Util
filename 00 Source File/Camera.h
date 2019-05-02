/**
* @file Camera.h
* @brief �J�����N���X��`�t�@�C��
* �r���[�E�v���W�F�N�V�����s��A�r���[�|�[�g�A���C���[�̃J�����O��������
* ��Ɍp�����Ďg�p���܂�
* @author Ryunosuke Honda.
*/
#pragma once

#include "Transform.h"

/**
*	�J�����N���X(�Œ��)
*/
class Camera : public Transform
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	Camera();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	virtual ~Camera() {}

	/**
	* @fn
	* �X�V����
	* @brief �p�����[�^����e�s��̐ݒ���s��
	*/
	virtual void update();

	/**
	* @fn
	* �J�����O���C���[�ݒ�
	* @brief ���C���[��ݒ肷�邱�Ƃł��̃J�����̉�ʕ`����s���Ƃ��ɃJ�����O����
	* @param (layer) �J�����O���������C���[(�ϒ�)
	* @detail ELayer�ȊO�̒l��ݒ肷��ƃR���p�C�����ɃG���[�ɂȂ�܂�
	*/
	template<typename... VA_Layer>
	inline void setCullingLayer(const VA_Layer&... layer)
	{
		mCullingLayer += calcLayerMask(layer...);
	}

	/**
	* @fn
	* �J�����O���邩�ǂ���
	* @param (layer) �`�F�b�N���郌�C���[
	* @return �J�����O���郌�C���[�Ȃ�true
	*/
	bool isCulling(const ELayer& layer) const;

private:
	/**
	* @fn
	* ���C���[�}�X�N�v�Z
	* @param (layer) ���Z���郌�C���[
	* @detail ���C���[�ݒ莞�ɂ̂݌Ăяo����܂�
	*/
	unsigned int calcLayerMask(const ELayer & layer);
	

private:
	///���N���X����
	using base = Transform;

protected:
	/**
	* @fn
	* �r���[�A�v���W�F�N�V�����s��̐ݒ�(�X�V)
	*/
	void calcViewProj();

	///�ȉ��v���p�e�B

	//!�����ʒu
	PROPERTY_READWRITE(Vector3, LookPt);
	//!������x�N�g��
	PROPERTY_READWRITE(Vector3, UpVec);
	//!�r���[�s��
	PROPERTY_READONLY(Matrix4x4, View);
	//!�v���W�F�N�V�����s��
	PROPERTY_READONLY(Matrix4x4, Proj);
	//!���̃J�������g�p���ĕ`�������Ƃ��Ɏg�p����r���[�|�[�g
	PROPERTY_READWRITE(D3D11_VIEWPORT, Viewport);
	//!���C���[�̃J�����O�Ɏg�������l�̖���
	using CullingLayer = unsigned int;
	//!���̃J�������g�p���ă����_�����O���s���Ƃ��ɃJ�����O����郌�C���[
	CullingLayer mCullingLayer;
};

/* End of File *****************************************************/