/**
* @file Factory.h
* @brief �t�@�N�g���[�p�^�[���̃x�[�X�N���X
* @detail �����\�Ȑ��i���Ǘ����邽�߁A�}�l�[�W���Ƃ͋�ʂ��Ē�`
* @author Ryunosuke Honda.
*/
#pragma once

#include <memory>
#include <unordered_map>

/**
*	�t�@�N�g���[�p�^�[���x�[�X�N���X
*/
template<class K, class V>
class Factory
{
	///�p����ŉ����ł���悤protected
protected:
	///�v�f���i�[����A�z�z��
	using ProductContainer = unordered_map<K, V*>;

public:
	/**
	* @fn
	* �N���[������
	* @brief �o�^�������i�����S�ɔj��
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
	* ���i�̓o�^
	* @brief Key"K", Value"V
	* @param (name) �L�[�̖��O
	* @param (product) �o�^���鐻�i
	*/
	void add(const K& name, V* product)
	{
		//���ɃL�[���o�^����Ă��Ȃ����`�F�b�N�A
		//�o�^����Ă�����L�[���R���\�[���ɏo�͂����^�[��
		if (isRegister(name))
		{
			cout << "�L�[����d�ɓo�^����Ă��܂�" << endl;
			return;
		}

		mProductContainer[name] = product;
	}

	/**
	* @fn
	* �o�^�������i���L�[���Q�Ƃ��Đ��Y
	* @param (name) �L�[�̖��O
	* @return ���i�̕���
	*/
	V* create(const K& name)
	{
		return mProductContainer[name]->clone();
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

	//!���i�R���e�i
	ProductContainer mProductContainer;					
};

/****** EOF *****************************************************/