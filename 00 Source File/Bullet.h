/**
* @file Bullet.h
* @brief �e�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "ACharacter.h"
#include "SphereCollider.h"
#include "OBJStaticMeshRenderDesc.h"

/**
*	�e�N���X
*/
class Bullet : public ACharacter, public SphereCollider
{
	///�萔
private:
	//!�e��
	static const float BULLET_SPEED;

public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (pos) �����ʒu
	* @param (dir) �i�s�����x�N�g��
	*/
	Bullet(const Vector3& pos, const Vector3& dir);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~Bullet();

	// ACharacter ����Čp������܂���
	virtual void init() override;
	virtual void fixedUpdate(float dt) override;
	virtual void draw(IRenderer & renderer) override;

	// ASphereCollider ����Čp������܂���
	virtual void onCollisionEnter(ACollider* other) override;

private:
	//!���f���`��L�q�q
	OBJStaticMeshRenderDesc mDesc;
};

/* End of File *****************************************************/