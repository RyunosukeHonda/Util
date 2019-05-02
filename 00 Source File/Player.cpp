/**
* @file Player.cpp
* @brief �v���C���[�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "Player.h"

///State
#include "PlayerIdle.h"
#include "PlayerRun.h"
#include "PlayerAiming.h"
#include "PlayerGameSet.h"

#include "IRenderer.h"
#include "IInput.h"
#include "Gun.h"
#include "Screen.h"
#include "PlayerSettingDesc.h"
#include "SoundManager.h"

Player::Player(const PlayerSettingDesc& settingDesc) :
	APlayableCharacter(settingDesc.mHP),
	SphereCollider(settingDesc.mRadius),
	mIndex(settingDesc.mIndex),
	mFrame(0),
	mCamera(this),
	mShot(new Gun(settingDesc.mGenerateBulletFunc)),
	mDesc(FBXSkinID::player),
	mDamageEffect(ShaderTextureID::MONOCHROME, 1.0f)
{
	//�^�O�ݒ�
	mTag = ETag::PLAYER;

	//�v���C���[�ԍ��ɉ������`�[���̃��C���[��ݒ�
	int index_to_layer = 2;
	Layer = static_cast<ELayer>(mIndex + index_to_layer);

	//�e�e�������ɃJ�����̏����g�p���邽�߃��C���[�Ƀ`�[���ԍ���o�^���Ă���
	mCamera.Layer = Layer;

	//�`��L�q�q�Ɏ��g��o�^
	mDesc.mpTransform = this;

	//�����ʒu�ݒ�
	Position = settingDesc.mPosition;
	mInitPosition = Position;

	//�X�e�[�g�̐���
	add(EPlayerState::IDLE, new PlayerIdle(this));
	add(EPlayerState::RUN, new PlayerRun(this));
	add(EPlayerState::AIMING, new PlayerAiming(this));
	add(EPlayerState::GAME_SET, new PlayerGameSet(this));
	initState(EPlayerState::IDLE);

	//���g���J�����O����悤�ݒ肷��
	mCamera.setCullingLayer(Layer);

	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = Screen::WINDOW_WIDTH;
	vp.Height = Screen::WINDOW_HEIGHT / 2;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = (Screen::WINDOW_HEIGHT / 2) * mIndex;
	mCamera.Viewport = vp;

	mDamageEffect.Position = { 0, (float)Screen::WINDOW_HEIGHT / 4.0f - (float)Screen::WINDOW_HEIGHT / 2.0f * (float)mIndex };
	mDamageEffect.Scale = { (float)Screen::WINDOW_WIDTH, (float)Screen::WINDOW_HEIGHT / 2.0f };
	mDamageEffect.setColor(Color4(1, 0, 0, 1));
}

Player::~Player()
{

}

void Player::rotateCamera(const Vector2 & amount)
{
	mCamera.RotateAmount += amount;
}

void Player::init()
{
	LocalPosition = mInitPosition;
	LocalEulerAngle = Vector3(0, 0, 0);

	float playerAngle = 3.14f * mIndex;
	float playerHeight = 0.8f;
	mCamera.init(Vector2(playerAngle, playerHeight));

	mStatus.init();
	initState(EPlayerState::IDLE);
}

void Player::lateUpdate(IInput & input)
{
	//�J�����̍X�V���s��
	mCamera.update();

	//�X�e�[�g�I���m�F
	stateEndCheck();
}

void Player::fixedUpdate(float dt)
{
	//�ړ�����
	mCurrentState->fixedUpdate(dt);
	//��������
	ARigidBody::fixedUpdate(dt);

	//�X�e�[�W�͈͊O�ɏo�Ȃ��悤�N�����v
	Position = {
		CLAMP(Position.x, -GameDef::STAGE_WIDTH, GameDef::STAGE_WIDTH),
		Position.y,
		CLAMP(Position.z, -GameDef::STAGE_WIDTH, GameDef::STAGE_WIDTH),
	};
}

void Player::update(IInput& input)
{
	mCurrentState->update(input);

	//�ˌ��͂��ł��s����
	mShot->update();
	if (input.getRightTrigger(mIndex) > 0.5f)
	{
		mShot->shot(&mCamera);
	}
}

void Player::draw(IRenderer & renderer)
{
	renderer.render(&mDesc);
	mDamageEffect.draw(renderer);
	mCurrentState->draw(renderer);
}

void Player::renderExecute(IRenderer & renderer)
{
	renderer.setRenderCamera(&mCamera);
	renderer.renderExecute();
}

void Player::gameSet()
{
	mCurrentState->gameSet();
}

void Player::onCollisionEnter(ACollider * other)
{
	if (other->Tag == ETag::BULLET)
	{
		int damagePoint = 10;
		mStatus.damage(damagePoint);
		SoundManager::instance().play(SoundID::HIT, false);
		mDamageEffect.init();
	}
	mCurrentState->onCollisionEnter(other);
}

void Player::onCollisionStay(ACollider * other)
{
}

void Player::onCollisionExit(ACollider * other)
{
}

void Player::move(const Vector2& amount)
{
	//�O������ړ�
	Vector3 v = mCamera.Forward * amount.y;
	v.y = 0;
	//D3DXVec3Normalize(&v, &v);
	LocalPosition += Vector3(v.x, 0, v.z);
	///FIXME Magic
	//���E�����ړ�
	v = mCamera.Forward * -amount.x;
	v.y = 0;
	//D3DXVec3Normalize(&v, &v);
	D3DXVec3Cross(&v, &v, &Vector3(0, 1, 0));
	LocalPosition += Vector3(v.x, 0, v.z);

	//���s�A�j���[�V�����i�߂�
	mFrame++;
	if (mFrame >= 25) mFrame = 0;
	mDesc.mFrame = mFrame * 4;
}

/* End of File *****************************************************/