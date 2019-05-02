/**
* @file SphereXSphereJudge.h
* @brief ���E�����m�̏Փ˔���N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;

class SphereCollider;
struct CSResult;
struct ID3D11ComputeShader;
struct ID3D11Buffer;
struct ID3D11ShaderResourceView;
struct ID3D11UnorderedAccessView;
struct ID3D11Buffer;

/**
*	���E�����m�̏Փ˔���N���X�ECollision�N���X�ł̂ݎg�p�����
*/
class SphereXSphereJudge
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	SphereXSphereJudge(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	
	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~SphereXSphereJudge();

	/**
	* @fn
	* ������s
	* @param (pDevice) �f�o�C�X�|�C���^
	* @param (pDeviceContext) �f�o�C�X�R���e�L�X�g�|�C���^
	* @param (sph1) ������s�����̃|�C���^�P
	* @param (sph2) ������s�����̃|�C���^�Q
	*/
	void judge(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, SphereCollider* sph1, SphereCollider* sph2);

private:
	//!������s���R���s���[�g�V�F�[�_�[
	ID3D11ComputeShader* mpSphereXSphereCS;
	//!����񑗐M�p�R���X�^���g�o�b�t�@�[
	ID3D11Buffer* mpSphereInfoBuffer;
	//!�f�[�^���͗p�V�F�[�_�[���\�[�X�r���[(SRV)
	ID3D11ShaderResourceView* mpBufferInputSRV;
	//!���ʎ��p�V�F�[�_�[�A�N�Z�X�r���[(UAV)
	ID3D11UnorderedAccessView* mpBufferResultUAV;
	//!���ʎ��o�b�t�@�[
	ID3D11Buffer* mpBufferResult;
	//!�v�Z���ʍ\���́Ecpp���Ŏg�p����̂͂���
	CSResult* mpResult;
};

/* End of File *****************************************************/