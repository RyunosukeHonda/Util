/**
* @file FPSCamera.h
* @brief FPS�J�����N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Camera.h"

/**
*	FPS�J�����N���X
*/
class FPSCamera : public Camera
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 * @param (follow) �Ǐ]�Ώ�
	 */
	FPSCamera(Transform* follow);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~FPSCamera();

	/**
	* @fn
	* ������
	*/
	void init(const Vector2& initRotateAmount);
	
	virtual void update() override;

protected:
	//!�J�����̉�]��
	PROPERTY_READWRITE(Vector2, RotateAmount);
	//!�����ƂȂ�Ǐ]����I�u�W�F�N�g�̃g�����X�t�H�[��
	Transform* mpObject;
	//!�Ǐ]�I�u�W�F�N�g�Ƃ̍���
	PROPERTY_WRITEONLY(Vector3, Offset);

private:
	using base = Camera;
};

/* End of File *****************************************************/