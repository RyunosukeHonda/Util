/**
* @file ResourceRenderer.h
* @brief ���\�[�X�`��Ɏg�p����N���X�e���v���[�g(�w�b�_�̂�)
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "Manager.h"
#include "MeshRenderDesc.h"
#include <vector>

class Camera;
struct DirectionalLightDesc;

/**
*	���\�[�X�`��N���X�p�e���v���[�g
*	D = MeshRenderDesc(���\�[�X�`��Ɏg�p����L�q�q)
*	K = Key(�A�z�z��o�^�Ɏg�p����ID)
*	V = Value(�A�z�z��ɓo�^����f�[�^�^�BManager���Ń|�C���^�ɕϊ�����܂�)
*/
template<
	class K,
	class V,
	class D = MeshRenderDesc
>
class ResourceRenderer : protected Manager<K, V>
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	ResourceRenderer() :
		mData()
	{}

	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~ResourceRenderer() {};

	void clear()
	{
		///�`��f�[�^�̊Ǘ����̂͊e�N���X�ōs���Ă���̂�
		///�����Ńf�B�[�v�N���A�͂���
		///�x�N�^�[�̃N���A�݂̂��s��
		mData.clear();
		mTransparentData.clear();
	}

	/**
	* @fn
	* ������
	* @brief ���`�����������߂ɕK�v�ȃp�����[�^�[��������
	* @param (pDevice) DirectX�`��@��
	* @return ����ɏI��������
	* @detail ���A�v���P�[�V�������ł͈�x�̂݌Ăяo�����Ώ\��
	*/
	virtual HRESULT init(ID3D11Device* pDevice) = 0;

	/**
	* @fn
	* �L�q�q�f�[�^�̓o�^
	* @brief �e�L�q�q���󂯎��A�A���t�@�l�ɂ���ēo�^��𕪊򂷂�
	* @param (D) �L�q�q�|�C���^
	*/
	void registerDesc(const D* pDesc)
	{
		//�ȈՂ̂��ߋL�q�q�̃f�B�t���[�Y�F�̃A���t�@�l�Ŕ���
		if (pDesc->mDiffuse.a > 0.999f)
		{
			mData.push_back(pDesc);
		}
		else
		{
			mTransparentData.push_back(pDesc);
		}
	}

	/**
	* @fn
	* ���b�V���`��(�s����)
	* @param (pDeviceContext) DirectX�`��@��
	* @param (camera) ���ۃJ�����N���X
	* @param (light) ���s����
	*/
	virtual void render(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light) = 0;

	/**
	* @fn
	* ���߃��b�V���`��
	* @param (pDeviceContext) DirectX�`��@��
	* @param (camera) ���ۃJ�����N���X
	* @param (light) ���s����
	*/
	virtual void renderTransparent(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light) = 0;

protected:
	//!�L�q�q�R���e�i����
	using RenderData = std::vector<const D*>;
	//!�s���߃I�u�W�F�N�g�f�[�^�i�[�R���e�i
	RenderData mData;
	//!���߃I�u�W�F�N�g�f�[�^�R���e�i
	RenderData mTransparentData;
};

/* End of File *****************************************************/