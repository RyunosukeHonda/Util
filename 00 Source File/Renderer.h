/**
* @file Renderer.h
* @brief �`��@�\�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IRenderer.h"
#include "Direct3D11.h"
#include "OBJStaticMeshRenderer.h"
#include "FBXHierarchyMeshRenderer.h"
#include "FBXSkinMeshRenderer.h"
#include "SpriteRenderer.h"
#include "QuadRenderer.h"
#include "DirectionalLightDesc.h"

/**
*	�`��@�\�N���X
*	DirectX�`��@�\��e���b�V���E�X�v���C�g�̕`��N���X�̒�����s��
*/
class Renderer : public IRenderer
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	*/
	Renderer(const HWND& wnd);

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~Renderer();

	// IRenderer ����Čp������܂���
	virtual void setRenderCamera(Camera * camera) override;
	virtual void setDirectionalLight(const DirectionalLightDesc& desc) override;
	virtual void load(const OBJMeshID& id, const LPSTR& fileName) override;
	virtual void load(const FBXHierarchyID& id, const LPSTR& fileName) override;
	virtual void load(const FBXSkinID& id, const LPSTR& fileName) override;
	virtual void load(const TextureID& id, const LPCWSTR& fileName) override;
	virtual void load(const ShaderTextureID & id, const LPCWSTR & fileName) override;
	virtual void render(const OBJStaticMeshRenderDesc * pDesc) override;
	virtual void render(const FBXHierarchyMeshRenderDesc* pDesc) override;
	virtual void render(const FBXSkinMeshRenderDesc * pDesc) override;
	virtual void render(const TextRenderDesc & desc) override;
	virtual void render(const SpriteRenderDesc * pDesc) override;
	virtual void render(const QuadRenderDesc * pDesc) override;
	virtual void render(const UIImageRenderDesc * pDesc) override;
	virtual void render(const UIQuadRenderDesc * pDesc) override;
	virtual void renderExecute() override;
	virtual void renderUI() override;
	virtual void clear() override;
	virtual void present() override;

private:
	/**
	* @fn
	* ����������
	* @brief DirectX11�@�\��e�����_�����O�N���X�̏��������s��
	* @detail �������Ɉ�x���������ŌĂяo���̂ő��Ŏg�p����K�v�͂Ȃ�
	*/
	void init();

private:
	//!DirectX�@�\�N���X
	Direct3D11 mDirect3D11;
	//!�����_�����O���s���J�����ݒ�p�̃|�C���^�E���̂̊Ǘ��͑��ōs���̂�delete�Ȃǂ͂��Ȃ�
	Camera* mpCamera;
	//!OBJ�X�^�e�B�b�N���b�V���`��N���X
	OBJStaticMeshRenderer mOBJStaticMeshRenderer;
	//!FBX�K�w���b�V���`��N���X
	FBXHierarchyMeshRenderer mFBXHierarchyMeshRenderer;
	//!FBX�X�L�����b�V���`��N���X
	FBXSkinMeshRenderer mFBXSkinMeshRenderer;
	//!�X�v���C�g�`��N���X
	SpriteRenderer mSpriteRenderer;
	//!��`�`��N���X
	QuadRenderer mQuadRenderer;
	//!���s����
	DirectionalLightDesc mLight;

	//!UI�`��p�r���[�|�[�g
	D3D11_VIEWPORT mUIPort;
	//!UI���W�n�A�r���[�s��ƕ��s���e�s����������킹���s��
	Matrix4x4 mUIMatrix;
};

/****** End of File *****************************************************/
