/**
* @file Quad.h
* @brief ��`�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	��`�N���X
*	�V�F�[�_�[�e�N�X�`����\��t���ăG�t�F�N�g�ɂ���
*/
class Quad : public CElement
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (pDevice) DirectX�`��@��
	* @param (fileName) �t�@�C����
	*/
	Quad(ID3D11Device* pDevice, LPCWSTR fileName);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~Quad();

	/**
	* @fn
	* �`��
	* @param (pDeviceContext) �`��f�o�C�X�R���e�L�X�g
	*/
	void render(ID3D11DeviceContext* pDeviceContext);

private:
	/**
	* @fn
	*	����������
	* @param (pDevice) DirectX�`��@��
	* @param (fileName) �t�@�C����
	*/
	void init(ID3D11Device* pDevice, LPCWSTR fileName);

private:
	//!�o�[�e�b�N�X�V�F�[�_�[
	ID3D11VertexShader* mpVertexShader;
	//!�s�N�Z���V�F�[�_�[
	ID3D11PixelShader* mpPixelShader;
	//!���_���C�A�E�g
	ID3D11InputLayout* mpVertexLayout;
	//!���_�o�b�t�@
	ID3D11Buffer* mpVertexBuffer;
};

/* End of File *****************************************************/