/**
* @file UIAppearingImage.h
* @brief ���X�Ɍ����摜�G�t�F�N�g�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "UIImageObject.h"
#include "Timer.h"

/**
*	���X�Ɍ����摜�G�t�F�N�g�N���X��`�t�@�C��
*/
class UIAppearingImage : public UIImageObject
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (id) �e�N�X�`��ID
	* @param (appearingTime) ����鎞��
	*/
	UIAppearingImage(const TextureID& id, float appearingTime);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~UIAppearingImage();

	/**
	* @fn
	* �������E�^�C�}�[�����������邱�Ƃœ����ɏ����Ă����G�t�F�N�g���n�܂�
	*/
	void init();

	virtual void draw(IRenderer& renderer) override;

private:
	//!���N���X����
	using base = UIImageObject;
	//!�����鎞�Ԍv���^�C�}�[
	Timer mTimer;
	//!���������Ԋi�[
	float mInitTime;
};

/* End of File *****************************************************/