/**
* @file Renderer.cpp
* @brief �`��@�\�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "Renderer.h"
#include "Singleton.h"

#include "OBJStaticMeshRenderDesc.h"
#include "TextRenderDesc.h"
#include "SpriteRenderDesc.h"

#include "Camera.h"
#include "Screen.h"

Renderer::Renderer(const HWND& wnd) :
	mDirect3D11(wnd),
	//mpFont(nullptr),
	mOBJStaticMeshRenderer(),
	mFBXSkinMeshRenderer(),
	mSpriteRenderer(),
	mLight()
{
	init();
}

Renderer::~Renderer()
{
	clear();
}
///FIXME wnd
void Renderer::init()
{
	///�e�`��N���X�̏�����

	mOBJStaticMeshRenderer.init(mDirect3D11.getDevicePointer());

	mFBXHierarchyMeshRenderer.init(mDirect3D11.getDevicePointer());

	mFBXSkinMeshRenderer.init(mDirect3D11.getDevicePointer());

	mSpriteRenderer.init(mDirect3D11.getDevicePointer());

	mQuadRenderer.init(mDirect3D11.getDevicePointer());

	//UI�p�r���[�|�[�g�̐ݒ�
	mUIPort.Width = Screen::WINDOW_WIDTH;
	mUIPort.Height = Screen::WINDOW_HEIGHT;
	mUIPort.MinDepth = 0.0f;
	mUIPort.MaxDepth = 1.0f;
	mUIPort.TopLeftX = 0;
	mUIPort.TopLeftY = 0;

	///UI�p���W�ϊ��s��̐ݒ�
	Matrix4x4 UIView;
	Vector3 eyePt(0.0f, 0.0f, -200); //�J�����i���_�j�ʒu
	Vector3 lookPt(0.0f, 0.0f, 0.0f);//�����ʒu
	Vector3 upVec(0.0f, 1.0f, 0.0f);//����ʒu
	D3DXMatrixLookAtLH(&UIView, &eyePt, &lookPt, &upVec);

	Matrix4x4 UIOrtho;
	D3DXMatrixOrthoLH(
		&UIOrtho,
		Screen::WINDOW_WIDTH,
		Screen::WINDOW_HEIGHT,
		Screen::NEAR_,
		Screen::FAR_);

	mUIMatrix = UIView * UIOrtho;
}

void Renderer::renderExecute()
{
	///�e���\�[�X�̖{�`��E�J�����O�g���b�N�̂��ߓ��߃I�u�W�F�N�g�̂ݓ��`����s���܂�

	//�w�ʃJ�����O��ԂőS�I�u�W�F�N�g��`��
	mDirect3D11.setCullBack();
	{
		mOBJStaticMeshRenderer.render(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXHierarchyMeshRenderer.render(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXSkinMeshRenderer.render(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mSpriteRenderer.render(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mQuadRenderer.render(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);

		mOBJStaticMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXHierarchyMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXSkinMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mSpriteRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mQuadRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
	}

	//�O�ʃJ�����O��Ԃœ��߃I�u�W�F�N�g�̂ݕ`��
	mDirect3D11.setCullFront();
	{
		mOBJStaticMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXHierarchyMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXSkinMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mSpriteRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mQuadRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
	}
}

void Renderer::renderUI()
{
	//UI�̕`��E�J�����O�𖳌����AUI�p�r���[�|�[�g�̐ݒ�
	mDirect3D11.setViewport(1, &mUIPort);
	mDirect3D11.setCullNone();
	{
		//�s���߃I�u�W�F�N�g�`��
		mSpriteRenderer.renderUI(mDirect3D11.getDeviceContextPointer(), mUIMatrix);
		mQuadRenderer.renderUI(mDirect3D11.getDeviceContextPointer(), mUIMatrix);

		//���߃I�u�W�F�N�g�`��
		mSpriteRenderer.renderTransparentUI(mDirect3D11.getDeviceContextPointer(), mUIMatrix);
		mQuadRenderer.renderTransparentUI(mDirect3D11.getDeviceContextPointer(), mUIMatrix);
	}
}

void Renderer::load(const OBJMeshID& id, const LPSTR & fileName)
{
	mOBJStaticMeshRenderer.addMesh(mDirect3D11.getDevicePointer(), id, fileName);
}

void Renderer::load(const FBXHierarchyID & id, const LPSTR & fileName)
{
	mFBXHierarchyMeshRenderer.addMesh(mDirect3D11.getDevicePointer(), id, fileName);
}

void Renderer::load(const FBXSkinID & id, const LPSTR & fileName)
{
	mFBXSkinMeshRenderer.addMesh(mDirect3D11.getDevicePointer(), id, fileName);
}

void Renderer::load(const TextureID & id, const LPCWSTR & fileName)
{
	mSpriteRenderer.addSprite(mDirect3D11.getDevicePointer(), id, fileName);
}

void Renderer::load(const ShaderTextureID & id, const LPCWSTR & fileName)
{
	mQuadRenderer.addQuad(mDirect3D11.getDevicePointer(), id, fileName);
}

void Renderer::render(const OBJStaticMeshRenderDesc * pDesc)
{
	mOBJStaticMeshRenderer.registerDesc(pDesc);
}

void Renderer::render(const FBXHierarchyMeshRenderDesc* pDesc)
{
	mFBXHierarchyMeshRenderer.registerDesc(pDesc);
}

void Renderer::render(const FBXSkinMeshRenderDesc * pDesc)
{
	mFBXSkinMeshRenderer.registerDesc(pDesc);
}

void Renderer::render(const TextRenderDesc & desc)
{
}

void Renderer::render(const SpriteRenderDesc * pDesc)
{
	mSpriteRenderer.registerDesc(pDesc);
}

void Renderer::render(const QuadRenderDesc * pDesc)
{
	mQuadRenderer.registerDesc(pDesc);
}

void Renderer::render(const UIImageRenderDesc * pDesc)
{
	mSpriteRenderer.registerUIData(pDesc);
}

void Renderer::render(const UIQuadRenderDesc * pDesc)
{
	mQuadRenderer.registerUIData(pDesc);
}

void Renderer::setRenderCamera(Camera* camera)
{
	mpCamera = camera;
	mDirect3D11.setViewport(1, &camera->Viewport);
}

void Renderer::setDirectionalLight(const DirectionalLightDesc & desc)
{
	mLight = desc;
}

void Renderer::clear()
{
	//�e�����_�����O�f�[�^�̃N���A
	mOBJStaticMeshRenderer.clear();
	mFBXHierarchyMeshRenderer.clear();
	mFBXSkinMeshRenderer.clear();
	mSpriteRenderer.clear();
	mQuadRenderer.clear();
	mSpriteRenderer.clearUI();
	mQuadRenderer.clearUI();

	//��ʃN���A
	mDirect3D11.clear();
}

void Renderer::present()
{
	mDirect3D11.present();
}

/****** End of File *****************************************************/
