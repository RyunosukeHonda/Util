/**
* @file UIDisappearingQuad.h
* @brief ���X�ɏ����Ă�����`�G�t�F�N�g�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "UIQuadObject.h"
#include "Timer.h"

/**
*	���X�ɏ����Ă�����`�G�t�F�N�g�N���X
*/
class UIDisappearingQuad : public UIQuadObject
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (id) �V�F�[�_�[ID
	* @param (disappearingTime) �����鎞��
	*/
	UIDisappearingQuad(const ShaderTextureID& id, float disappearingTime);

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~UIDisappearingQuad();

	/**
	* @fn
	* �������E�^�C�}�[�����������邱�Ƃœ����ɏ����Ă����G�t�F�N�g���n�܂�
	*/
	void init();

	virtual void draw(IRenderer& renderer) override;

private:
	//!���N���X����
	using base = UIQuadObject;
	//!�����鎞�Ԍv���^�C�}�[
	Timer mTimer;
	//!���������Ԋi�[
	float mInitTime;
};

/* End of File *****************************************************/