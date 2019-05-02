/**
* @file SoundManager.h
* @brief �����\�[�X�Ǘ��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "Manager.h"
#include "SoundID.h"
#include "Sound.h"
#include "Singleton.h"

/**
*	�����\�[�X�Ǘ��N���X(�V���O���g��)
*/
class SoundManager :
	private Manager<SoundID, Sound>,
	public Singleton<SoundManager>
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	SoundManager();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~SoundManager();

	/**
	* @fn
	* �T�E���h�ǂݍ���
	* @param (id) ���\�[�X�Ǘ��ԍ�
	* @param (fileName) �ǂݍ��ރt�@�C����
	*/
	void load(const SoundID &id, char* fileName);

	/**
	* @fn
	* �T�E���h�Đ�
	* @param (id) ���\�[�X�Ǘ��ԍ�
	* @param (isLoop) ���[�v�Đ����邩
	*/
	void play(const SoundID &id, bool isLoop);

	/**
	* @fn
	* �T�E���h��~
	* @param (id) ���\�[�X�Ǘ��ԍ�
	*/
	void stop(const SoundID& id);
	
	/**
	* @fn
	* �T�E���h�폜
	* @param (id) ���\�[�X�Ǘ��ԍ�
	*/
	void remove(const SoundID& id);

	/**
	* @fn
	* �T�E���h�S�폜
	*/
	void clear();

private:
	/**
	* @fn
	* ������
	* @return �����������ǂ���
	*/
	void init();

	//!XAudio2�@�\�C���^�[�t�F�C�X
	IXAudio2* mpXAudio2;
	//!�}�X�^�����O�{�C�X
	IXAudio2MasteringVoice* mpMasteringVoice;
};

/* End of File *****************************************************/