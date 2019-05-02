/**
* @file Manager.h
* @brief �A�z�z����Ǘ�����}�l�[�W���[�̃x�[�X�N���X
* @detail �������ꂽ���Ȃ��v�f���Ǘ����邽�߁A�t�@�N�g���[�Ƃ͋�ʂ��Ē�`
* @author Ryunosuke Honda.
*/
#pragma once

#include <unordered_map>
#include <memory>

/**
*	�}�l�[�W���[�x�[�X�N���X
*/
template<class K, class V>
class Manager
{
	///�p����ŉ����ł���悤protected
protected:
	///�v�f�|�C���^
	using ProductPointer = shared_ptr<V>;
	///�v�f���i�[����A�z�z��
	using ProductContainer = unordered_map<K, ProductPointer>;

public:
	/**
	* @fn
	* �N���[������
	* @brief �o�^�����v�f�����S�ɔj��
	*/
	void clear()
	{
		ProductContainer::iterator i = mProductContainer.begin();
		while (i != mProductContainer.end()) {
			delete i->second;
			++i;
		}
	}

	/**
	* @fn
	* �v�f�̓o�^
	* @brief Key"K", Value"V
	* @param (name) �L�[�̖��O
	* @param (product) �o�^����v�f
	* @detail �v�f�͎����I��shared_pointer�ɕϊ�����܂�
	*/
	void add(const K& name, V* product)
	{
		//���ɃL�[���o�^����Ă��Ȃ����`�F�b�N�A
		//�o�^����Ă�����L�[���R���\�[���ɏo�͂����^�[��
		if (isRegister(name))
		{
			Debug::log("�L�[����d�ɓo�^����Ă��܂�");
			return;
		}

		mProductContainer[name] = ProductPointer(product);
	}

	/**
	* @fn
	* �o�^�����v�f�̎Q�Ƃ��擾
	* @param (name) �L�[�̖��O
	* @return �v�f�̃|�C���^
	* @detail �����s�܂��͕����̕K�v���Ȃ��v�f���擾����
	*/
	ProductPointer get(const K& name)
	{
		return mProductContainer[name];
	}

private:
	/**
	* @fn
	* �L�[�����ɓo�^����Ă��邩����
	* @param (name) �L�[�̖��O
	* @return ���ɓo�^����Ă����true
	*/
	bool isRegister(const K& name)
	{
		return mProductContainer.count(name) != 0;
	}

private:
	//!�v�f�R���e�i
	ProductContainer mProductContainer;
};

/****** EOF *****************************************************/