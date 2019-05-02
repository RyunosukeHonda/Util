/**
* @file Bullet.cpp
* @brief �e�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "Bullet.h"

#include "IRenderer.h"

const float Bullet::BULLET_SPEED = 30.0f;

Bullet::Bullet(const Vector3& pos, const Vector3& dir) :
	ACharacter(1),
	SphereCollider(0.3f),
	mDesc(OBJMeshID::bullet)
{
	mTag = ETag::BULLET;
	mPosition = pos;
	mForward = dir;
	mDesc.mpTransform = this;
}

Bullet::~Bullet()
{
}

void Bullet::init()
{
}

void Bullet::fixedUpdate(float dt)
{
	Position += Forward * dt * BULLET_SPEED;

	//�X�e�[�W�͈͊O�Ȃ�e�����ŁE�����͓K���Ȓl�Ŕ���
	int maxHeight = 20.0f;
	if (
		abs(Position.x) > GameDef::STAGE_WIDTH ||
		Position.y > maxHeight ||
		abs(Position.z) > GameDef::STAGE_WIDTH)
	{
		mStatus.damage(1);
	}
}

void Bullet::draw(IRenderer & renderer)
{
	//�ǂ��炪�������e���킩��悤�Ƀ��C���[�ɂ���ĐF��ύX
	if (Layer == ELayer::BULLET1)
	{
		mDesc.mDiffuse = { 0, -1, 1, 0.5f };
		mDesc.mSpecular = { 1, 1, 1, 1 };
	}
	else if (Layer == ELayer::BULLET2)
	{
		mDesc.mDiffuse = { 1, -1, 0, 0.5f };
		mDesc.mSpecular = { 1, 1, 1, 1 };
	}

	renderer.render(&mDesc);
}

void Bullet::onCollisionEnter(ACollider * other)
{
	mStatus.damage(1);
}

/* End of File *****************************************************/