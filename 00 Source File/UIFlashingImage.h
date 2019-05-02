/**
* @file UIFlashingImage.h
* @brief UI�摜�ɓ_�ŋ@�\��ǉ������N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "UIImageObject.h"
#include "Timer.h"

/**
*	UI�摜�ɓ_�ŋ@�\��ǉ������N���X
*/
class UIFlashingImage : public UIImageObject
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	UIFlashingImage(const TextureID& id, float time);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	virtual ~UIFlashingImage();

	virtual void draw(IRenderer& renderer) override;

protected:
	//!�_�ŊԊu�v���^�C�}�[
	Timer mTimer;
	//!�\���t���O
	bool mEnable;

private:
	using base = UIImageObject;
};

/* End of File *****************************************************/