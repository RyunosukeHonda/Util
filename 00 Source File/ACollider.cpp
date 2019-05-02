/**
* @file ACollider.cpp
* @brief ���ۃR���C�_�[�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "ACollider.h"

ACollider::ACollider(const ERigidType& type) :
	base(type),
	mInfo()
{
}

ACollider::~ACollider()
{
	//���̃N���A�̂݁B���̂̍폜�͍s���܂���
	mInfo.clear();
}

void ACollider::result(ACollider * other, bool isCol)
{
	//�Փˏ��ۊǃ}�b�v�ɃR���C�_�[���o�^����Ă��Ȃ����
	if (mInfo.count(other) == 0)
	{
		//�Փ�(isCol)��ۊ�
		mInfo[other] = isCol;
		//�Փ˂��Ă����Enter���ĂсA���^�[��
		if (isCol)
			onCollisionEnter(other);
		return;
	}

	//�ȉ��͏Փ˂������ǂ����ŕ���
	//�Փ˂��Ă����ꍇ
	if (isCol)
	{
		//�O�t���[���̏Փˏ��ŌĂяo���֐���I��
		//�O�t���[���ŏՓ˂��Ă��Ȃ�����
		if (mInfo[other] == false)
		{
			//�Փ�(true)��ۊ�
			mInfo[other] = true;
			//Enter,Stay���Ăяo�����^�[��
			onCollisionEnter(other);
			onCollisionStay(other);
			return;
		}

		//�O�t���[���ŏՓ˂��Ă�����
		//Stay���Ăяo�����^�[��(�ۊǂ̕K�v�Ȃ�)
		onCollisionStay(other);
		return;
	}

	//�Փ˂��Ă��Ȃ������ꍇ
	//�O�t���[���ŏՓ˂��Ă����Exit���Ăяo��
	if (mInfo[other] == true)
	{
		//�Փˏ��(false)��ۊ�
		mInfo[other] = false;
		onCollisionExit(other);
	}

	//***************
	//�����ɂ��ǂ蒅���Ă�����
	//�O�t���[���ŏՓ˂��Ă��Ȃ��A
	//���t���[�����Փ˂��Ă��Ȃ��Ƃ������Ƃ�
	//�����͓��ɂȂ�
	//***************
}

bool ACollider::isInvalid() const
{
	//���C���[�񋓌^�̏I�[�ȏ�̐��l�Ȃ�s��
	return static_cast<unsigned int>(mLayer) > static_cast<unsigned int>(ELayer::LAYER_END);
}

/* End of File *****************************************************/