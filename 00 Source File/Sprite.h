/**
* @file Sprite.h
* @brief �X�v���C�g�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	�X�v���C�g�N���X
*/
class Sprite : public CElement
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (pDevice) �`��f�o�C�X
	* @param (fileName) �ǂݍ��ރt�@�C����
	*/
	Sprite(ID3D11Device* pDevice, LPCWSTR fileName);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~Sprite();

	/**
	* @fn
	* �`��
	* @param (pDeviceContext) �`��f�o�C�X
	*/
	void render(ID3D11DeviceContext* pDeviceContext);

private:
	/**
	* @fn
	* ������
	* @param (pDevice) �`��f�o�C�X
	* @param (fileName) �ǂݍ��ރt�@�C����
	*/
	void init(ID3D11Device* pDevice, LPCWSTR fileName);

private:
	//!���_�o�b�t�@
	ID3D11Buffer* mpVertexBuffer;
	//!�e�N�X�`���[�̃T���v���[
	ID3D11SamplerState* mpSampleLinear;
	//!�e�N�X�`���[
	ID3D11ShaderResourceView* mpTexture;
};

/* End of File *****************************************************/