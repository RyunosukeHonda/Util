/**
* @file ELayer.h
* @brief ���C���[�񋓌^�E�`��A�Փ˔��莞�Ȃǂ�Transform�̕��ނɎg�p
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @enum ELayer
* ���C���[�񋓌^
*/
enum ELayer : unsigned int
{
	//!�f�t�H���g�A���ɐݒ肪�K�v�Ȃ��ꍇ�E���C���[�}�X�N�Ɏg�p���邽�߂P�ŏ�����
	DEFAULT = 1,
	//!�`�[��1�E�v���C���[�P�ɓK�p
	TEAM1,
	//!�`�[���Q�E�v���C���[�Q�ɓK�p
	TEAM2,
	//!�`�[���P�̏e�e�E�`�[���Q�ƏՓ�
	BULLET1,
	//!�`�[���Q�̏e�e�E�`�[���P�ƏՓ�
	BULLET2,
	//!�I�[�E����ȏ�̐��l�̓G���[
	LAYER_END,
};

/****** End of File *****************************************************/
