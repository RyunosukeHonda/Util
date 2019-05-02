/**
* @file IRenderer.h
* @brief �`��@�\�C���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "OBJStaticMeshID.h"
#include "FBXHierarchyMeshID.h"
#include "FBXSkinMeshID.h"
#include "TextureID.h"
#include "ShaderTextureID.h"

struct OBJStaticMeshRenderDesc;
struct FBXHierarchyMeshRenderDesc;
struct FBXSkinMeshRenderDesc;
struct TextRenderDesc;
struct SpriteRenderDesc;
struct QuadRenderDesc;
struct UIImageRenderDesc;
struct UIQuadRenderDesc;
struct DirectionalLightDesc;

class Camera;

/**
*	�����_���[�C���^�[�t�F�[�X
*/
class IRenderer
{
public:
	/**
	* @fn
	* ���z�f�X�g���N�^
	*/
	virtual ~IRenderer() {};

	/**
	* @fn
	* �����_�����O���s���J������ݒ�
	* @param (camera) �J�����̃|�C���^
	*/
	virtual void setRenderCamera(Camera* camera) = 0;

	/**
	* @fn
	* �����_�����O���Ɏg�p���镽�s������ݒ�
	* @param (desc) ���s�������L�q�q
	*/
	virtual void setDirectionalLight(const DirectionalLightDesc& desc) = 0;

	/**
	* @fn
	* ���\�[�X�ǂݍ���
	* @brief OBJ�`���X�^�e�B�b�N���b�V���̃��[�h���s��
	* @param (id) OBJ���b�V���Ǘ�ID
	* @param (fileName) �ǂݍ��ރt�@�C����
	*/
	virtual void load(const OBJMeshID& id, const LPSTR& fileName) = 0;

	/**
	* @fn
	* ���\�[�X�ǂݍ���
	* @brief FBX�`���X�L�����b�V���̃��[�h���s��
	* @param (id) FBX�X�L�����b�V���Ǘ�ID
	* @param (fileName) �ǂݍ��ރt�@�C����
	*/
	virtual void load(const FBXHierarchyID& id, const LPSTR& fileName) = 0;

	/**
	* @fn
	* ���\�[�X�ǂݍ���
	* @brief FBX�`���X�L�����b�V���̃��[�h���s��
	* @param (id) FBX�X�L�����b�V���Ǘ�ID
	* @param (fileName) �ǂݍ��ރt�@�C����
	*/
	virtual void load(const FBXSkinID& id, const LPSTR& fileName) = 0;

	/**
	* @fn
	* ���\�[�X�ǂݍ���
	* @brief �X�v���C�g(���m�ɂ͎g�p����e�N�X�`��)�̃��[�h���s��
	* @param (id) �e�N�X�`���Ǘ�ID
	* @param (fileName) �ǂݍ��ރt�@�C����
	*/
	virtual void load(const TextureID& id, const LPCWSTR& fileName) = 0;

	/**
	* @fn
	* ���\�[�X�ǂݍ���
	* @brief ��`�ɓ\��t���Ďg�p����V�F�[�_�[�e�N�X�`���̃��[�h���s��
	* @param (id) �V�F�[�_�[�e�N�X�`���Ǘ�ID
	* @param (fileName) �ǂݍ��ރt�@�C����
	*/
	virtual void load(const ShaderTextureID& id, const LPCWSTR& fileName) = 0;

	/**
	* @fn
	* �`��
	* @brief OBJ�`���̃X�^�e�B�b�N���b�V���̕`����s��
	* @param (desc) OBJ���b�V���`��L�q�q
	* @detail ���ۂɍs���͕̂`��f�[�^�̓o�^����
	*/
	virtual void render(const OBJStaticMeshRenderDesc* pDesc) = 0;

	/**
	* @fn
	* �`��
	* @brief FBX�`���̊K�w���b�V���̕`����s��
	* @param (pDesc) OBJ���b�V���`��L�q�q
	* @detail ���ۂɍs���͕̂`��f�[�^�̓o�^����
	*/
	virtual void render(const FBXHierarchyMeshRenderDesc* pDesc) = 0;

	/**
	* @fn
	* �`��
	* @brief FBX�`���̃X�L�����b�V���̕`����s��
	* @param (pDesc) OBJ���b�V���`��L�q�q
	* @detail ���ۂɍs���͕̂`��f�[�^�̓o�^����
	*/
	virtual void render(const FBXSkinMeshRenderDesc* pDesc) = 0;

	/**
	* @fn
	* �`��
	* @brief �e�L�X�g�̕`����s��
	* @param (desc) �e�L�X�g�`��L�q�q
	* @detail DirectX10�W���@�\���g�p�B�d���̂Ŏ�Ƀf�o�b�O�p
	*/
	virtual void render(const TextRenderDesc& desc) = 0;

	/**
	* @fn
	* �`��
	* @brief �X�v���C�g�̕`����s��
	* @param (pDesc) �X�v���C�g�`��L�q�q
	* @detail ���ۂɍs���͕̂`��f�[�^�̓o�^����
	*/
	virtual void render(const SpriteRenderDesc* pDesc) = 0;

	/**
	* @fn
	* �`��
	* @brief �l�p�ƃ|���S��(�V�F�[�_�[�e�N�X�`���t�^)�̕`����s��
	* @param (pDesc) ��`�`��L�q�q
	* @detail ���ۂɍs���͕̂`��f�[�^�̓o�^����
	*/
	virtual void render(const QuadRenderDesc* pDesc) = 0;

	/**
	* @fn
	* �`��
	* @brief UI���W�n�ŉ摜�̕`����s��
	* @param (pDesc) UI�摜�`��L�q�q
	* @detail ���ۂɍs���͕̂`��f�[�^�̓o�^����
	*/
	virtual void render(const UIImageRenderDesc* pDesc) = 0;

	/**
	* @fn
	* �`��
	* @brief UI���W�n�ŃV�F�[�_�[��\��t������`�̕`����s��
	* @param (pDesc) UI��`�`��L�q�q
	* @detail ���ۂɍs���͕̂`��f�[�^�̓o�^����
	*/
	virtual void render(const UIQuadRenderDesc* pDesc) = 0;

	/**
	* @fn
	* �`����s
	* @brief �o�^���ꂽ�`��f�[�^�����ۂɕ`�悷��
	*/
	virtual void renderExecute() = 0;

	/**
	* @fn
	* UI�`����s
	* @brief �o�^���ꂽUI�`��f�[�^�����ۂɕ`�悷��
	* @detail ���f���`�悪�S�ďI��������ƂɎ��s����
	*/
	virtual void renderUI() = 0;

	/**
	* @fn
	* ��ʃN���A
	*/
	virtual void clear() = 0;

	/**
	* @fn
	* ��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	*/
	virtual void present() = 0;
};

/****** End of File *****************************************************/
