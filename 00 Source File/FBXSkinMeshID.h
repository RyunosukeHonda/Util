/**
* @file FBXSkinMeshID.h
* @brief OBJ�^�X�^�e�B�b�N���b�V���Ǘ��ԍ��񋓌^
* @author Ryunosuke Honda.
*/
#pragma once

#include "StringEnumBase.h"
#include <iostream>

using namespace std;

/**
*	OBJ���f��ID
*/
class FBXSkinMeshID
{
public:
	/*******************************
	�g�p����ID�͂����ɂ܂Ƃ߂�
	********************************/
	ENUM(FBX_SKIN_ID,
		player,
		enemy
	)

		FBXSkinMeshID::FBX_SKIN_ID::type LoadID(string& key) {
		if (FBX_SKIN_ID.converter.find(key) != FBX_SKIN_ID.converter.end()) {
			return FBX_SKIN_ID.converter[key];
		}
		else
		{
			cout << "FBXSkinMeshID [ " << key.c_str() << " ] is not found." << endl;
		}
	}

};

using FBXSkinID = FBXSkinMeshID::FBX_SKIN_ID::type;

/****** End of File *****************************************************/
