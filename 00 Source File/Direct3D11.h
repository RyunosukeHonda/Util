/**
* @file Direct3D11.h
* @brief Direct3D11�`��@�\�Ǘ��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

/**
*	Direct3D11�`��@�\�Ǘ��N���X
*/
class Direct3D11 : public CElement
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (wnd) �E�B���h�E�n���h��
	*/
	Direct3D11(const HWND& wnd);

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~Direct3D11();

	/**
	* @fn
	* �r���[�|�[�g�ݒ�
	* @param (viewportNum) �r���[�|�[�g�ԍ�
	* @param (viewport) �r���[�|�[�g�L�q�q
	*/
	void setViewport(const int viewportNum, const D3D11_VIEWPORT* viewport);
	
	/**
	* @fn
	* ��ʃN���A
	*/
	void clear();

	/**
	* @fn
	* ��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	*/
	HRESULT present();

	/**
	* @fn
	* �O�ʃJ�����O�ݒ��K�p
	*/
	void setCullFront();

	/**
	* @fn
	* �w�ʃJ�����O�ݒ��K�p
	*/
	void setCullBack();

	/**
	* @fn
	* �J�����O�Ȃ��ݒ��K�p
	* @brief
	* UI���J�����O����ƌ����ɂ���Ă͌����Ȃ��Ȃ��Ă��܂��̂�
	* UI�`�掞�����J�����O��؂�
	*/
	void setCullNone();

	/**
	* @fn
	* �f�o�C�X�|�C���^�̎擾
	*/
	ID3D11Device* getDevicePointer();

	/**
	* @fn
	* �f�o�C�X�R���e�L�X�g�|�C���^�̎擾
	*/
	ID3D11DeviceContext* getDeviceContextPointer();

private:
	/**
	* @fn
	* �������E��x�s����Ώ\���Ȃ��ߐ������ɍs��
	*/
	HRESULT init(const HWND& wnd);

private:
	//!DirectX�f�o�C�X
	ID3D11Device* mpDevice;
	//!DirectX�f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* mpDeviceContext;
	//!�X���b�v�`�F�C��
	IDXGISwapChain* mpSwapChain;
	//!�����_�[�^�[�Q�b�g
	ID3D11RenderTargetView* mpRenderTargetView;
	//!�f�v�X
	ID3D11DepthStencilView* mpDepthStencilView;
	//!�f�v�X�X�e���V��
	ID3D11Texture2D* mpDepthStencil;
	//!�O�ʃJ�����O�X�e�[�g
	ID3D11RasterizerState* mpRasterizerStateFront;
	//!�w�ʃJ�����O�X�e�[�g
	ID3D11RasterizerState* mpRasterizerStateBack;
	//!�J�����O�������X�e�[�g
	ID3D11RasterizerState* mpRasterizerStateNone;
	//!�u�����h�X�e�[�g
	ID3D11BlendState* mpBlendState;
	//!�f�v�X�X�e���V���X�e�[�g
	ID3D11DepthStencilState* mpDepthStencilState;
};

/****** End of File *****************************************************/